#include "pch.h"
#include "HierarchyWindow.h"
#include "HierarchyWindowImpl.h"

HierarchyWindow::HierarchyWindow(QWidget* parent) : QDockWidget(parent) {}

HierarchyWindow* HierarchyWindow::CreateImpl(std::shared_ptr<pawn::Scene>& scene, QWidget* parent) {
	return new impl::HierarchyWindowImpl(scene, parent);
}