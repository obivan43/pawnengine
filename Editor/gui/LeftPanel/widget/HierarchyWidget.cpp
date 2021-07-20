#include "HierarchyWidget.h"

#include "Editor/gui/LeftPanel/widget/impl/HierarchyWidgetImpl.h"

namespace editor {

	HierarchyWidget::HierarchyWidget(QWidget* parent) : QWidget(parent) {}

	HierarchyWidget* HierarchyWidget::CreateImpl(QWidget* parent) {
		return new impl::HierarchyWidgetImpl(parent);
	}

}
