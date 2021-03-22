#include "pch.h"
#include "TransformationComponentWidgetItem.h"

namespace impl {

	TransformationComponentWidgetItem::TransformationComponentWidgetItem(QTreeWidget* parent)
		: QTreeWidgetItem(parent)
		, m_TransformationComponentWidget(nullptr)
		, m_WidgetWrapper(nullptr)
		, m_Entity(nullptr) {
		m_WidgetWrapper = new QTreeWidgetItem(this);
		m_TransformationComponentWidget = new TransformationComponentWidget(parent);

		setText(0, "Transformation");
		addChild(m_WidgetWrapper);
	}

	TransformationComponentWidgetItem::TransformationComponentWidgetItem(QTreeWidget* parent, pawn::Entity* entity)
		: QTreeWidgetItem(parent)
		, m_TransformationComponentWidget(nullptr)
		, m_WidgetWrapper(nullptr)
		, m_Entity(entity) {
		m_WidgetWrapper = new QTreeWidgetItem(this);
		m_TransformationComponentWidget = new TransformationComponentWidget(parent);

		if (m_Entity) {
			m_TransformationComponentWidget->SetTransformation(&m_Entity->GetComponent<pawn::TransformationComponent>());
		}

		setText(0, "Transformation");
		addChild(m_WidgetWrapper);
	}

	void TransformationComponentWidgetItem::SetEntity(pawn::Entity* entity) {
		m_Entity = entity;
		if (m_Entity && !m_Entity->IsNull()) {
			m_TransformationComponentWidget->SetTransformation(&m_Entity->GetComponent<pawn::TransformationComponent>());
		}
	}

}