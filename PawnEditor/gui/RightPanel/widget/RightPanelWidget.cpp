#include "RightPanelWidget.h"
#include "PawnEditor/gui/RightPanel/widget/impl/RightPanelWidgetImpl.h"

RightPanelWidget::RightPanelWidget(QWidget* parent) : QDockWidget(parent) {}

RightPanelWidget* RightPanelWidget::CreateImpl(QWidget* parent) {
	return new impl::RightPanelWidgetImpl(parent);
}
