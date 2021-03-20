#pragma once

#include "OutputWindow.h"
#include "OutputStream.h"

#include <QtWidgets/QTextEdit>

namespace impl {

	class OutputWindowImpl : public OutputWindow {
		Q_OBJECT

		public:
			OutputWindowImpl(QWidget* parent);

		private:
			QTextEdit* m_OutputTextEdit;
			OutputStream* m_OutputStream;
	};

}
