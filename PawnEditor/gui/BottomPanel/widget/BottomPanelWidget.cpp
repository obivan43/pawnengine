#include "BottomPanelWidget.h"
#include "PawnEditor/gui/BottomPanel/widget/impl/BottomPanelWidgetImpl.h"

BottomPanelWidget::BottomPanelWidget(QWidget* parent) : QDockWidget(parent) {}

BottomPanelWidget* BottomPanelWidget::CreateImpl(QWidget* parent) {
	return new impl::BottomPanelWidgetImpl(parent);
}
