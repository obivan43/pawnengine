#include "PawnUtils/utils/logger/Logger.h"
#include "PawnSystem/system/windows/SystemPC.h"
#include "PawnSystem/system/windows/InputManagerWindows.h"
#include "PawnNetwork/network/Network.h"
#include "PawnNetwork/network/api/Api.h"
#include "PawnEngine/engine/Engine.h"

#include <memory>
#include <future>

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#endif

#ifdef PAWN_NETWORK

#pragma comment (lib, "Ws2_32.lib")

#endif

std::atomic<bool> isRunning = true;
std::mutex mutex;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	LRESULT result{ 0 };
	
	switch (msg) {
		case WM_CLOSE:
			isRunning = false;
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_INPUT:
		case WM_INPUT_DEVICE_CHANGE:
			pawn::system::InputManagerWindows::WinHandle(msg, wParam, lParam, &result);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

#ifdef PAWN_NETWORK
void NetworkThread(std::shared_ptr<pawn::engine::Engine>& engine) {
	std::shared_ptr<pawn::network::Network> network(new pawn::network::Network);
	std::shared_ptr<pawn::network::Api> api(new pawn::network::Api(engine, network));
	network->Init();

	while (isRunning) {
		int recive = network->Receive();

		if (recive > 0) {
			api->Handle(network->Data());
			CONSOLE_INFO("recived {}", recive)
		}
	}

	network->Shutdown();
}
#endif

void GameThread(HWND hwnd) {
	pawn::utils::Logger::Init();

	std::shared_ptr<pawn::engine::Engine> engine(new pawn::engine::Engine);

	SetGameEngineWindowHWND(hwnd);

	pawn::system::InputManagerWindows::RegisterMouse();
	pawn::system::InputManagerWindows::RegisterKeyboard();

	engine->Init(hwnd, 1280, 720);

	pawn::utils::Clock m_Clock;
	m_Clock.Reset();

	engine->GetScriptEngine()->SetIsPaused(false);

	const int32_t fpsLock = 144;
	auto next_frame = std::chrono::steady_clock::now();

#ifdef PAWN_NETWORK
	std::future<void> future = std::async(std::launch::async, NetworkThread, std::ref(engine));
#endif

	engine->OnCreate();
	while (engine->GetEngineRunning()) {
		std::lock_guard<std::mutex> guard(mutex);
		std::this_thread::sleep_until(next_frame);

		next_frame += std::chrono::milliseconds(1000 / fpsLock);

		m_Clock.Tick();

		engine->Clear();
		engine->OnInput();
		engine->OnUpdate(m_Clock);
		engine->OnRender();

		if (!isRunning) {
			engine->SetEngineRunning(false);
		}
	}

	future.wait();
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
#ifdef _WIN32
	CreateConsoleOutput();
#endif

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"window";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"window",
		L"pawn engine",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	std::future<void> future = std::async(std::launch::async, GameThread, hwnd);

	while (isRunning) {
		BOOL result = PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);

		if (result) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}

	future.wait();

	return static_cast<int>(Msg.wParam);
}