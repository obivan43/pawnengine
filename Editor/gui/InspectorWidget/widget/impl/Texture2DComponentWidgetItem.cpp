#include "Texture2DComponentWidgetItem.h"

#include "PawnEngine/engine/components/MeshComponent.h"

namespace editor::impl {

	Texture2DComponentWidgetItem::Texture2DComponentWidgetItem(QTreeWidget* parent)
		: QTreeWidgetItem(parent)
		, m_Texturee2DComponentWidget(nullptr)
		, m_WidgetWrapper(nullptr)
		, m_Entity(nullptr) {
		m_WidgetWrapper = new QTreeWidgetItem(this);
		m_Texturee2DComponentWidget = new Texture2DComponentWidget(parent);

		setText(0, "Texture2D");
		addChild(m_WidgetWrapper);

		InitConnections();
	}

	void Texture2DComponentWidgetItem::SetEntity(pawn::engine::GameEntity* entity) {
		m_Entity = entity;
		if (m_Entity && !m_Entity->IsNull() && m_Entity->HasComponent<pawn::engine::Texture2DComponent>()) {
			m_Texturee2DComponentWidget->SetEntity(entity);
			m_Texturee2DComponentWidget->SetTexture2D(&m_Entity->GetComponent<pawn::engine::Texture2DComponent>());
		}
	}

	void Texture2DComponentWidgetItem::InitConnections() {
		qRegisterMetaType<pawn::engine::GameEntity>("pawn::engine::GameEntity");
		connect(
			m_Texturee2DComponentWidget,
			SIGNAL(Texture2DModified(pawn::engine::GameEntity)),
			this,
			SIGNAL(EntityTexture2DModified(pawn::engine::GameEntity)),
			Qt::QueuedConnection
		);
	}

}
