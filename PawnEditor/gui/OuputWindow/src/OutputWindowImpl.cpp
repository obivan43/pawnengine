#include "pch.h"
#include "OutputWindowImpl.h"

namespace impl {

	OutputWindowImpl::OutputWindowImpl(QWidget* parent) : OutputWindow(parent) {
		m_OutputTextEdit = new QTextEdit(this);
		m_OutputTextEdit->setReadOnly(true);

		setWindowTitle("Output");
		setWidget(m_OutputTextEdit);

		m_OutputStream = new OutputStream(std::cout, m_OutputTextEdit);
		OutputStream::registerConsoleMessageHandler();
	}

}