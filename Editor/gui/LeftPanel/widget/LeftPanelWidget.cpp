#include "LeftPanelWidget.h"

#include "Editor/gui/LeftPanel/widget/impl/LeftPanelWidgetImpl.h"

namespace editor {

	LeftPanelWidget::LeftPanelWidget(QWidget* parent) : QDockWidget(parent) {}

	LeftPanelWidget* LeftPanelWidget::CreateImpl(QWidget* parent) {
		return new impl::LeftPanelWidgetImpl(parent);
	}

}
