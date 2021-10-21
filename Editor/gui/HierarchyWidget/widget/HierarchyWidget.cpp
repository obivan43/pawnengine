#include "HierarchyWidget.h"

#include "Editor/gui/HierarchyWidget/widget/impl/HierarchyWidgetImpl.h"

namespace editor {

	HierarchyWidget::HierarchyWidget(QWidget* parent) : QWidget(parent) {}

	void HierarchyWidget::SetEngineManager(std::shared_ptr<impl::EngineManager>& engineManager) {
		m_EngineManager = engineManager;
	}

	std::shared_ptr<impl::EngineManager> HierarchyWidget::GetEngineManager() {
		return m_EngineManager;
	}

	HierarchyWidget* HierarchyWidget::CreateImpl(QWidget* parent) {
		return new impl::HierarchyWidgetImpl(parent);
	}

}
