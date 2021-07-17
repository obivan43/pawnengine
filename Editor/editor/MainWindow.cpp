#include "MainWindow.h"
#include "impl/MainWindowImpl.h"

namespace editor {

	MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), Running(true), m_Engine(nullptr) {}

	MainWindow* MainWindow::CreateImpl(QWidget* parent) {
		return new impl::MainWindowImpl(parent);
	}

}
