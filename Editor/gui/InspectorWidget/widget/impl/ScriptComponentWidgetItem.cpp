#include "ScriptComponentWidgetItem.h"

namespace editor {

	namespace impl {

		ScriptComponentWidgetItem::ScriptComponentWidgetItem(QTreeWidget* parent)
			: QTreeWidgetItem(parent)
			, m_ScriptComponentWidget(nullptr)
			, m_WidgetWrapper(nullptr)
			, m_Entity(nullptr) {

			m_WidgetWrapper = new QTreeWidgetItem(this);
			m_ScriptComponentWidget = new ScriptComponentWidget(parent);

			setText(0, "Script");
			addChild(m_WidgetWrapper);

			InitConnections();
		}

		void ScriptComponentWidgetItem::SetEntity(pawn::engine::GameEntity* entity) {
			m_Entity = entity;
			if (m_Entity && !m_Entity->IsNull() && m_Entity->HasComponent<pawn::engine::ScriptComponent>()) {
				m_ScriptComponentWidget->SetScript(&m_Entity->GetComponent<pawn::engine::ScriptComponent>());
			}
		}

		void ScriptComponentWidgetItem::InitConnections() {
			connect(
				m_ScriptComponentWidget,
				SIGNAL(ScriptModified()),
				this,
				SIGNAL(EntityScriptModified()),
				Qt::QueuedConnection
			);
		}

	}

}
