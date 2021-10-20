#include "MeshComponentWidgetItem.h"

#include "PawnEngine/engine/components/MeshComponent.h"

namespace editor::impl {

	MeshComponentWidgetItem::MeshComponentWidgetItem(QTreeWidget* parent)
		: QTreeWidgetItem(parent)
		, m_MeshComponentWidget(nullptr)
		, m_WidgetWrapper(nullptr)
		, m_Entity(nullptr) {
		m_WidgetWrapper = new QTreeWidgetItem(this);
		m_MeshComponentWidget = new MeshComponentWidget(parent);

		setText(0, "Mesh");
		addChild(m_WidgetWrapper);

		InitConnections();
	}

	void MeshComponentWidgetItem::SetEntity(pawn::engine::GameEntity* entity) {
		m_Entity = entity;
		if (m_Entity && !m_Entity->IsNull() && m_Entity->HasComponent<pawn::engine::MeshComponent>()) {
			m_MeshComponentWidget->SetEntity(entity);
			m_MeshComponentWidget->SetMesh(&m_Entity->GetComponent<pawn::engine::MeshComponent>());
		}
	}

	void MeshComponentWidgetItem::InitConnections() {
		qRegisterMetaType<pawn::engine::GameEntity>("pawn::engine::GameEntity");
		connect(
			m_MeshComponentWidget,
			SIGNAL(MeshModified(pawn::engine::GameEntity)),
			this,
			SIGNAL(EntityMeshModified(pawn::engine::GameEntity)),
			Qt::QueuedConnection
		);
	}

}
