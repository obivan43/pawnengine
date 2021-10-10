#include "EngineViewWidget.h"

#include "Editor/gui/EngineViewWidget/widget/impl/EngineViewWidgetImpl.h"

namespace editor {

	EngineViewWidget::EngineViewWidget(QWidget* parent) : QWidget(parent) {}

	EngineViewWidget* EngineViewWidget::CreateImpl(QWidget* parent) {
		return new impl::EngineViewWidgetImpl(parent);
	}

}

