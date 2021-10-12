#include "MainWindow.h"
#include "impl/MainWindowImpl.h"

namespace editor {

	MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_Engine(nullptr) {}

	MainWindow* MainWindow::CreateImpl(QApplication* application, QWidget* parent) {
		return new impl::MainWindowImpl(application, parent);
	}

}
