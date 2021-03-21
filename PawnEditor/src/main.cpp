#include "pch.h"
#include "MainWindow.h"

#include <QtWidgets/QApplication>
#include <QtCore>

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#endif

int main(int argc, char *argv[]) {
    pawn::Logger::Init();

    QApplication app(argc, argv);
	QFile file(":/dark.qss");
	if (file.open(QFile::ReadOnly | QFile::Text)) {
		QTextStream stream(&file);
		app.setStyleSheet(stream.readAll());
	}

    QSharedPointer<MainWindow> window = QSharedPointer<MainWindow>(MainWindow::CreateImpl());
    window->show();

    pawn::Clock m_Clock;
    m_Clock.Reset();

    pawn::Engine* engine = window->GetEngine();
	while (window->Running) {
        m_Clock.Tick();
        engine->Clear();

        app.processEvents();

        engine->OnUpdate(m_Clock);

        engine->SwapBuffers();
	}
    window.clear();

    app.exit();
}