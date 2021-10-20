#include "MainWindow.h"
#include "impl/WindowsEventFilter.h"

#include "PawnUtils/utils/logger/Logger.h"

#include "PawnGraphics/graphics/directx/debug/DirectX11Exception.h"
#include "PawnSystem/system/windows/SystemPC.h"

#include <QtCore>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QApplication>

#include <chrono>
#include <thread>
#include <exception>

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")

#endif

void GameThread(pawn::engine::Engine* engine) {
	pawn::utils::Clock m_Clock;
	m_Clock.Reset();

	auto next_frame = std::chrono::steady_clock::now();
	const int32_t fpsLock = 144;

	try {
		engine->OnCreate();
		while (engine->GetEngineRunning()) {
			next_frame += std::chrono::milliseconds(1000 / fpsLock);

			m_Clock.Tick();

			engine->Clear();
			engine->OnInput();
			engine->OnUpdate(m_Clock);
			engine->OnRender();

			std::this_thread::sleep_until(next_frame);
		}
	}
	catch (const pawn::graphics::DirectX11Exception& e) {
#ifdef _WIN32
		MessageBoxA(nullptr, e.what(), "DirectX11 exception", MB_OK | MB_ICONEXCLAMATION);
		exit(-1);
#endif
	}
	catch (const std::exception& e) {
#ifdef _WIN32
		MessageBoxA(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION);
		exit(-1);
#endif
	}
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
#ifdef PAWN_CONSOLE_OUTPUT
	CreateConsoleOutput();
#endif
#endif

	pawn::utils::Logger::Init();

	QApplication app(argc, argv);
	app.installNativeEventFilter(new editor::impl::WindowsEventFilter());

	try {
		editor::MainWindow* window = editor::MainWindow::CreateImpl(&app);
		window->show();

		QFuture<void> future = QtConcurrent::run(GameThread, window->GetEngine());
	}
	catch (const pawn::graphics::DirectX11Exception& e) {
#ifdef _WIN32
		MessageBoxA(nullptr, e.what(), "DirectX11 exception", MB_OK | MB_ICONEXCLAMATION);
		exit(-1);
#endif
	}
	catch (const std::exception& e) {
#ifdef _WIN32
		MessageBoxA(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION);
		exit(-1);
#endif
	}

	return app.exec();
}
