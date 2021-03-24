#include "pch.h"
#include "TagComponentWidgetItem.h"

namespace impl {

	TagComponentWidgetItem::TagComponentWidgetItem(QTreeWidget* parent)
		: QTreeWidgetItem(parent)
		, m_TagLineEdit(nullptr)
		, m_WidgetWrapper(nullptr)
		, m_Entity(nullptr) {
		m_WidgetWrapper = new QTreeWidgetItem(this);
		m_TagLineEdit = new QLineEdit(parent);

		setText(0, "Tag");
		addChild(m_WidgetWrapper);

		InitConnections();
	}

	void TagComponentWidgetItem::OnLineEditPress() {
		QString& text = m_TagLineEdit->text();

		if (m_Entity && !m_Entity->IsNull()) {
			std::string& tag = m_Entity->GetComponent<pawn::TagComponent>().Tag;
			tag = text.toLocal8Bit().constData();
		}

		emit EntityTagModified();
		m_TagLineEdit->clearFocus();
	}

	void TagComponentWidgetItem::InitConnections() {
		connect(
			m_TagLineEdit,
			SIGNAL(returnPressed()),
			SLOT(OnLineEditPress())
		);
	}

}
