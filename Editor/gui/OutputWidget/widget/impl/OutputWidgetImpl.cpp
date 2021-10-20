#include "OutputWidgetImpl.h"

#include <QHBoxLayout>

namespace editor::impl {

	OutputWidgetImpl::OutputWidgetImpl(QWidget* parent) : OutputWidget(parent) {
		m_OutputTextEdit = new QTextEdit(this);
		m_OutputTextEdit->setReadOnly(true);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->addWidget(m_OutputTextEdit);

		setLayout(layout);

		m_OutputStream = new OutputStream(std::cout);

		InitConections();

		OutputStream::registerConsoleMessageHandler();
	}

	void OutputWidgetImpl::OnTextChanged() {
		m_OutputTextEdit->moveCursor(QTextCursor::End);
	}

	void OutputWidgetImpl::InitConections() {
		connect(
			m_OutputStream,
			SIGNAL(ColorChanged(const QColor&)),
			m_OutputTextEdit,
			SLOT(SetTextColor(const QColor&))
		);

		connect(
			m_OutputStream,
			SIGNAL(InsertText(const QString&)),
			m_OutputTextEdit,
			SLOT(insertPlainText(const QString&))
		);

		connect(
			m_OutputStream,
			SIGNAL(Append(const QString&)),
			m_OutputTextEdit,
			SLOT(append(const QString&))
		);

		connect(
			m_OutputTextEdit,
			SIGNAL(textChanged()),
			this,
			SLOT(OnTextChanged())
		);
	}

}
