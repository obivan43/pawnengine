#include "TransformationComponentWidgetItem.h"

namespace editor {

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

		void TransformationComponentWidgetItem::SetEntity(pawn::engine::GameEntity* entity) {
			m_Entity = entity;
			if (m_Entity && !m_Entity->IsNull()) {
				m_TransformationComponentWidget->SetTransformation(&m_Entity->GetComponent<pawn::engine::TransformationComponent>());
			}
		}

	}

}
