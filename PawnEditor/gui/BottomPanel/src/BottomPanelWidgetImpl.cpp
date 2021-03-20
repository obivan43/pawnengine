#include "pch.h"
#include "BottomPanelWidgetImpl.h"

namespace impl {

	BottomPanelWidgetImpl::BottomPanelWidgetImpl(QWidget* parent) : BottomPanelWidget(parent) {
		m_OutputTextEdit = new QTextEdit(this);
		m_OutputTextEdit->setReadOnly(true);

		setWindowTitle("Output");
		setWidget(m_OutputTextEdit);

		m_OutputStream = new OutputStream(std::cout, m_OutputTextEdit);
		OutputStream::registerConsoleMessageHandler();
	}

}