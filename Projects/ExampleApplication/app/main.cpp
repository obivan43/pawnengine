#include "PawnUtils/utils/logger/Logger.h"
#include "PawnSystem/system/windows/SystemPC.h"
#include "PawnSystem/system/windows/InputManagerWindows.h"
#include "PawnSystem/system/input/KeyboardManager.h"
#include "PawnSystem/system/input/KeyboardButton.h"
#include "PawnNetwork/network/Network.h"
#include "PawnNetwork/network/api/Api.h"
#include "PawnEngine/engine/Engine.h"
#include "PawnEngine/engine/EngineGlobals.h"
#include "PawnGraphics/graphics/directx/debug/DirectX11Exception.h"

#include <memory>
#include <future>

#define WINDOW_W 1920
#define WINDOW_H 1080

#undef PAWN_NETWORK

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

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
		case WM_SETCURSOR:
			if (LOWORD(lParam) == HTCLIENT) {
				SetCursor(NULL);
			}
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

	try {
		std::shared_ptr<pawn::engine::Engine> engine(new pawn::engine::Engine);

		SetGameEngineWindowHWND(hwnd);

		pawn::system::InputManagerWindows::RegisterMouse();
		pawn::system::InputManagerWindows::RegisterKeyboard();

		engine->Init(hwnd, WINDOW_W, WINDOW_H);

		pawn::utils::Clock m_Clock;
		m_Clock.Reset();

		engine->GetScriptEngine()->SetIsPaused(false);

		const int32_t fpsLock = 144;
		auto next_frame = std::chrono::steady_clock::now();

#ifdef PAWN_NETWORK
		std::future<void> future = std::async(std::launch::async, NetworkThread, std::ref(engine));
#endif

		engine->UploadMeshFromFile("res/assets/models/cube.fbx");
		engine->UploadMeshFromFile("res/assets/models/sphere.fbx");
		engine->UploadMeshFromFile("res/assets/models/cylinder.fbx");
		engine->UploadMeshFromFile("res/assets/models/cone.fbx");
		engine->UploadMeshFromFile("res/assets/models/torus.fbx");
		engine->UploadMeshFromFile("res/assets/models/plane.fbx");
		engine->UploadMeshFromFile("res/assets/models/handgun.fbx");

		engine->UploadTextureFromFile("res/assets/textures/brick_C.jpg");
		engine->UploadTextureFromFile("res/assets/textures/wall_C.jpg");
		engine->UploadTextureFromFile("res/assets/textures/wall_N.jpg");
		engine->UploadTextureFromFile("res/assets/textures/handgun_C.jpg");
		engine->UploadTextureFromFile("res/assets/textures/handgun_N.jpg");
		engine->UploadTextureFromFile("res/assets/textures/handgun_S.jpg");

		engine->LoadState("res/assets/scenes/basicScene.pawn");


		engine->OnCreate();
		while (engine->GetEngineRunning()) {
			std::lock_guard<std::mutex> guard(mutex);
			std::this_thread::sleep_until(next_frame);

			next_frame += std::chrono::milliseconds(1000 / fpsLock);

			m_Clock.Tick();

			engine->Clear();
			engine->OnInput();

			if (pawn::system::KeyboardManager::ButtonPressed(pawn::system::Button::Escape)) {
				isRunning = false;
			}

			engine->OnUpdate(m_Clock);
			engine->OnRender();

			if (!isRunning) {
				engine->SetEngineRunning(false);
			}
		}
	}
	catch (const pawn::graphics::DirectX11Exception& e) {
#ifdef _WIN32
		MessageBoxA(nullptr, e.what(), "DirectX11 exception", MB_OK | MB_ICONEXCLAMATION);
#endif
	}
	catch (const std::exception& e) {
#ifdef _WIN32
		MessageBoxA(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION);
#endif
	}

	isRunning = false;

#ifdef PAWN_NETWORK
	future.wait();
#endif
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
#if defined _WIN32 && defined _DEBUG
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
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_W, WINDOW_H,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	RECT rect;
	GetClientRect(hwnd, &rect);
	MapWindowPoints(hwnd, nullptr, reinterpret_cast<POINT*>(&rect), 2);
	ClipCursor(&rect);

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