#include "CentralWidget.h"
#include "CentralWidgetImpl.h"

CentralWidget::CentralWidget(QWidget* parent) : QFrame(parent) {}

CentralWidget* CentralWidget::CreateImpl(QWidget* parent) {
	return new impl::CentralWidgetImpl(parent);
}