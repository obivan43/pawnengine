#include "pch.h"
#include "LeftPanelWidget.h"
#include "LeftPanelWidgetImpl.h"

LeftPanelWidget::LeftPanelWidget(QWidget* parent) : QDockWidget(parent) {}

LeftPanelWidget* LeftPanelWidget::CreateImpl(std::shared_ptr<pawn::Scene>& scene, QWidget* parent) {
	return new impl::LeftPanelWidgetImpl(scene, parent);
}