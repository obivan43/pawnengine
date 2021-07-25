#include "EngineViewWidget.h"

#include "Editor/gui/EngineViewWidget/widget/impl/EngineViewWidgetImpl.h"

namespace editor {

	EngineViewWidget::EngineViewWidget(QWidget* parent) : QFrame(parent) {}

	EngineViewWidget* EngineViewWidget::CreateImpl(QWidget* parent) {
		return new impl::EngineViewWidgetImpl(parent);
	}

}
