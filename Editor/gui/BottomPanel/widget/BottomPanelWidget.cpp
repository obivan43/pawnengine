#include "BottomPanelWidget.h"

#include "Editor/gui/BottomPanel/widget/impl/BottomPanelWidgetImpl.h"

namespace editor {

	BottomPanelWidget::BottomPanelWidget(QWidget* parent) : QDockWidget(parent) {}

	BottomPanelWidget* BottomPanelWidget::CreateImpl(QWidget* parent) {
		return new impl::BottomPanelWidgetImpl(parent);
	}

}
