#include "CameraComponentWidgetItem.h"

namespace editor {

	namespace impl {

		CameraComponentWidgetItem::CameraComponentWidgetItem(QTreeWidget* parent)
			: QTreeWidgetItem(parent)
			, m_CameraComponentWidget(nullptr)
			, m_WidgetWrapper(nullptr)
			, m_Entity(nullptr) {
			m_WidgetWrapper = new QTreeWidgetItem(this);
			m_CameraComponentWidget = new CameraComponentWidget(parent);

			setText(0, "Camera");
			addChild(m_WidgetWrapper);
		}

		void CameraComponentWidgetItem::SetEntity(pawn::engine::GameEntity* entity) {
			m_Entity = entity; 
			if (m_Entity && !m_Entity->IsNull() && m_Entity->HasComponent<pawn::engine::CameraComponent>()) {
				m_CameraComponentWidget->SetCamera(&m_Entity->GetComponent<pawn::engine::CameraComponent>());
			}
		}

	}

}
