#include "OutputWidgetImpl.h"

#include <QHBoxLayout>

namespace editor {

	namespace impl {

		OutputWidgetImpl::OutputWidgetImpl(QWidget* parent) : OutputWidget(parent) {
			m_OutputTextEdit = new QTextEdit(this);
			m_OutputTextEdit->setReadOnly(true);

			QHBoxLayout* layout = new QHBoxLayout(this);
			layout->addWidget(m_OutputTextEdit);

			setLayout(layout);

			m_OutputStream = new OutputStream(std::cout, m_OutputTextEdit);
			OutputStream::registerConsoleMessageHandler();
		}

	}

}
