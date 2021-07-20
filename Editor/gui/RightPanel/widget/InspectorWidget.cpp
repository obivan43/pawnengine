#include "InspectorWidget.h"

#include "Editor/gui/RightPanel/widget/impl/InspectorWidgetImpl.h"

namespace editor {

	InspectorWidget::InspectorWidget(QWidget* parent) : QWidget(parent) {}

	InspectorWidget* InspectorWidget::CreateImpl(QWidget* parent) {
		return new impl::InspectorWidgetImpl(parent);
	}

}
