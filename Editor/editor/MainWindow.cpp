#include "MainWindow.h"
#include "impl/MainWindowImpl.h"

namespace editor {

	MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_Engine(nullptr) {}

	MainWindow* MainWindow::CreateImpl(QWidget* parent) {
		return new impl::MainWindowImpl(parent);
	}

}
