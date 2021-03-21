#include "pch.h"
#include "MainWindow.h"
#include "MainWindowImpl.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), Running(true), m_Engine(nullptr) {}

MainWindow* MainWindow::CreateImpl(QWidget* parent) {
	return new impl::MainWindowImpl(parent);
}