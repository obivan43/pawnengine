#pragma once

#include "OutputStream.h"

#include "Editor/gui/OutputWidget/widget/OutputWidget.h"

#include <QtWidgets/QTextEdit>

namespace editor {

	namespace impl {

		class OutputWidgetImpl : public OutputWidget {
				Q_OBJECT

			public:
				OutputWidgetImpl(QWidget* parent);

			private:
				QTextEdit* m_OutputTextEdit;
				OutputStream* m_OutputStream;
		};

	}

}
