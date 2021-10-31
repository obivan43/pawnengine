#include "DirectionalLightWidgetItem.h"

namespace editor::impl {

	DirectionalLightWidgetItem::DirectionalLightWidgetItem(QTreeWidget* parent)
		: QTreeWidgetItem(parent)
		, m_DirectionalLightWidget(nullptr)
		, m_WidgetWrapper(nullptr)
		, m_Entity(nullptr) {
		m_WidgetWrapper = new QTreeWidgetItem(this);
		m_DirectionalLightWidget = new DirectionalLightWidget(parent);

		setText(0, "Directional light");
		addChild(m_WidgetWrapper);
	}

	void DirectionalLightWidgetItem::SetEntity(pawn::engine::GameEntity* entity) {
		m_Entity = entity;
		if (m_Entity && !m_Entity->IsNull() && m_Entity->IsValid() && m_Entity->HasComponent<pawn::engine::DirectionalLightComponent>()) {
			m_DirectionalLightWidget->SetDirectionalLight(&m_Entity->GetComponent<pawn::engine::DirectionalLightComponent>());
		}
	}

}
