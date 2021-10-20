#include "EngineViewWidgetImpl.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace editor::impl {

	EngineViewWidgetImpl::EngineViewWidgetImpl(QWidget* parent)
		: EngineViewWidget(parent)
		, m_EngineFrame(nullptr) {
		
		QVBoxLayout* layout = new QVBoxLayout(this);

		m_EngineFrame = new QFrame();

		layout->addWidget(m_EngineFrame);

		setLayout(layout);
	}

}
