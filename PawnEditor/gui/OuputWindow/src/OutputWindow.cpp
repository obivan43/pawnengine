#include "pch.h"
#include "OutputWindow.h"
#include "OutputWindowImpl.h"

OutputWindow::OutputWindow(QWidget* parent) : QDockWidget(parent) {}

OutputWindow* OutputWindow::createImpl(QWidget* parent) {
	return new impl::OutputWindowImpl(parent);
}