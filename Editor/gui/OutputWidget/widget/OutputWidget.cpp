#include "OutputWidget.h"

#include "Editor/gui/OutputWidget/widget/impl/OutputWidgetImpl.h"

namespace editor {

	OutputWidget::OutputWidget(QWidget* parent) : QWidget(parent) {}

	OutputWidget* OutputWidget::CreateImpl(QWidget* parent) {
		return new impl::OutputWidgetImpl(parent);
	}

}
