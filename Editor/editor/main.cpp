#include "MainWindow.h"
#include "impl/WindowsEventFilter.h"

#include "PawnUtils/utils/logger/Logger.h"

#include "PawnSystem/system/windows/SystemPC.h"

#include <QtCore>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QApplication>

#include <chrono>
#include <thread>

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#endif

void GameThread(pawn::engine::Engine* engine) {
	pawn::utils::Clock m_Clock;
	m_Clock.Reset();

	auto next_frame = std::chrono::steady_clock::now();
	const int32_t fpsLock = 144;

	engine->OnCreate();
	while (engine->GetEngineRunning()) {
		next_frame += std::chrono::milliseconds(1000 / fpsLock);

		m_Clock.Tick();

		engine->Clear();
		engine->OnInput();
		engine->OnUpdate(m_Clock);
		engine->OnRender(m_Clock);

		std::this_thread::sleep_until(next_frame);
	}
}

int main(int argc, char *argv[]) {
#ifdef _WIN32
#ifdef PAWN_CONSOLE_OUTPUT
	CreateConsoleOutput();
#endif
#endif

    pawn::utils::Logger::Init();

    QApplication app(argc, argv);
    app.installNativeEventFilter(new editor::impl::WindowsEventFilter());

	editor::MainWindow* window = editor::MainWindow::CreateImpl();
	window->show();

	QFuture<void> future = QtConcurrent::run(GameThread, window->GetEngine());

    return app.exec();
}
