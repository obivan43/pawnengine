#include "CentralWidget.h"
#include "PawnEditor/gui/CentralWidget/widget/impl/CentralWidgetImpl.h"

CentralWidget::CentralWidget(QWidget* parent) : QFrame(parent) {}

CentralWidget* CentralWidget::CreateImpl(QWidget* parent) {
	return new impl::CentralWidgetImpl(parent);
}
