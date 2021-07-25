#include "HierarchyWidget.h"

#include "Editor/gui/HierarchyWidget/widget/impl/HierarchyWidgetImpl.h"

namespace editor {

	HierarchyWidget::HierarchyWidget(QWidget* parent) : QWidget(parent) {}

	void HierarchyWidget::SetEngineManager(impl::EngineManager* engineManager) {
		m_EngineManager = engineManager;
	}

	HierarchyWidget* HierarchyWidget::CreateImpl(QWidget* parent) {
		return new impl::HierarchyWidgetImpl(parent);
	}

}
