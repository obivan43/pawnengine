#include "LeftPanelWidget.h"
#include "LeftPanelWidgetImpl.h"

LeftPanelWidget::LeftPanelWidget(QWidget* parent) : QDockWidget(parent) {}

LeftPanelWidget* LeftPanelWidget::CreateImpl(QWidget* parent) {
	return new impl::LeftPanelWidgetImpl(parent);
}