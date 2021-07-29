#include "TagComponentWidgetItem.h"

#include "PawnEngine/engine/components/TagComponent.h"

namespace editor {

	namespace impl {

		TagComponentWidgetItem::TagComponentWidgetItem(QTreeWidget* parent)
			: QTreeWidgetItem(parent)
			, m_TagComponentWidget(nullptr)
			, m_WidgetWrapper(nullptr)
			, m_Entity(nullptr) {

			m_WidgetWrapper = new QTreeWidgetItem(this);
			m_TagComponentWidget = new TagComponentWidget(parent);

			setText(0, "Tag");
			addChild(m_WidgetWrapper);

			InitConnections();
		}

		void TagComponentWidgetItem::SetEntity(pawn::engine::GameEntity* entity) {
			m_Entity = entity;
			if (m_Entity && !m_Entity->IsNull() && m_Entity->HasComponent<pawn::engine::TagComponent>()) {
				m_TagComponentWidget->SetTag(&m_Entity->GetComponent<pawn::engine::TagComponent>());
			}
		}

		void TagComponentWidgetItem::InitConnections() {
			connect(
				m_TagComponentWidget,
				SIGNAL(TagModified()),
				this,
				SIGNAL(EntityTagModified()),
				Qt::QueuedConnection
			);
		}

	}

}
