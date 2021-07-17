#pragma once

#include "OutputStream.h"

#include "Editor/gui/BottomPanel/widget/BottomPanelWidget.h"

#include <QtWidgets/QTextEdit>

namespace editor {

	namespace impl {

		class BottomPanelWidgetImpl : public BottomPanelWidget {
				Q_OBJECT

			public:
				BottomPanelWidgetImpl(QWidget* parent);

			private:
				QTextEdit* m_OutputTextEdit;
				OutputStream* m_OutputStream;
		};

	}

}
