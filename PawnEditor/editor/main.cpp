#include "MainWindow.h"
#include "impl/WindowsEventFilter.h"

#include "PawnUtils/utils/logger/Logger.h"

#include <QtCore>
#include <QtWidgets/QApplication>

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#endif

int main(int argc, char *argv[]) {
    pawn::utils::Logger::Init();

    QApplication app(argc, argv);
	QFile file(":/dark.qss");
	if (file.open(QFile::ReadOnly | QFile::Text)) {
		QTextStream stream(&file);
		app.setStyleSheet(stream.readAll());
	}

    app.installNativeEventFilter(new impl::WindowsEventFilter());

    QSharedPointer<MainWindow> window = QSharedPointer<MainWindow>(MainWindow::CreateImpl());
    window->show();

    pawn::utils::Clock m_Clock;
    m_Clock.Reset();

    pawn::engine::Engine* engine = window->GetEngine();
	while (window->Running) {
        m_Clock.Tick();
        engine->Clear();

        app.processEvents();

        engine->OnInput();
        engine->OnUpdate(m_Clock);

        engine->SwapBuffers();
	}
    window.clear();

    app.exit();
}