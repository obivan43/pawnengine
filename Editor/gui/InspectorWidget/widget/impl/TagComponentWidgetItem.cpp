#include "TagComponentWidgetItem.h"

#include "PawnEngine/engine/components/TagComponent.h"

namespace editor {

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

		void TagComponentWidgetItem::SetEntity(pawn::engine::GameEntity* entity) {
			m_Entity = entity;
			if (m_Entity && !m_Entity->IsNull() && m_Entity->HasComponent<pawn::engine::TagComponent>()) {
				m_TagLineEdit->setText(m_Entity->GetComponent<pawn::engine::TagComponent>().Tag.c_str());
			}
		}

		void TagComponentWidgetItem::OnLineEditPress() {
			QString& text{ m_TagLineEdit->text() };

			if (m_Entity && !m_Entity->IsNull()) {
				std::string& tag{ m_Entity->GetComponent<pawn::engine::TagComponent>().Tag };
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

}
