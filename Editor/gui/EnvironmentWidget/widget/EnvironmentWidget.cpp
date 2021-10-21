#include "EnvironmentWidget.h"

#include "Editor/gui/EnvironmentWidget/widget/impl/EnvironmentWidgetImpl.h"

namespace editor {

	EnvironmentWidget::EnvironmentWidget(QWidget* parent) : QWidget(parent) {}

	void EnvironmentWidget::SetEngineManager(std::shared_ptr<impl::EngineManager>& engineManager) {
		m_EngineManager = engineManager;
	}

	std::shared_ptr<impl::EngineManager> EnvironmentWidget::GetEngineManager() {
		return m_EngineManager;
	}

	EnvironmentWidget* EnvironmentWidget::CreateImpl(QWidget* parent) {
		return new impl::EnvironmentWidgetImpl(parent);
	}

}

