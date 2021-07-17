#include "RightPanelWidget.h"

#include "Editor/gui/RightPanel/widget/impl/RightPanelWidgetImpl.h"

namespace editor {

	RightPanelWidget::RightPanelWidget(QWidget* parent) : QDockWidget(parent) {}

	RightPanelWidget* RightPanelWidget::CreateImpl(QWidget* parent) {
		return new impl::RightPanelWidgetImpl(parent);
	}

}
