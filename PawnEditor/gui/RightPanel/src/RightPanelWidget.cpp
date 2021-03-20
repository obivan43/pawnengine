#include "pch.h"
#include "RightPanelWidget.h"
#include "RightPanelWidgetImpl.h"

RightPanelWidget::RightPanelWidget(QWidget* parent) : QDockWidget(parent) {}

RightPanelWidget* RightPanelWidget::CreateImpl(QWidget* parent) {
	return new impl::RightPanelWidgetImpl(parent);
}