#include "MainWindow.h"
#include "impl/WindowsEventFilter.h"

#include "PawnUtils/utils/logger/Logger.h"

#include <QtCore>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QApplication>

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#endif

void GameThread(pawn::engine::Engine* engine) {
	pawn::utils::Clock m_Clock;
	m_Clock.Reset();

	engine->OnCreate();
	while (engine->GetEngineRunning()) {
		m_Clock.Tick();

		engine->Clear();
		engine->OnInput();
		engine->OnUpdate(m_Clock);
		engine->OnRender(m_Clock);
	}
}

int main(int argc, char *argv[]) {
    pawn::utils::Logger::Init();

    QApplication app(argc, argv);
    app.installNativeEventFilter(new editor::impl::WindowsEventFilter());

	editor::MainWindow* window = editor::MainWindow::CreateImpl();
	window->show();

	QFuture<void> future = QtConcurrent::run(GameThread, window->GetEngine());

    return app.exec();
}
