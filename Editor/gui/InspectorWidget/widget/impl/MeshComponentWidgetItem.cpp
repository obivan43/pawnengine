#include "MeshComponentWidgetItem.h"

#include "PawnEngine/engine/components/MeshComponent.h"

namespace editor {

	namespace impl {

		MeshComponentWidgetItem::MeshComponentWidgetItem(QTreeWidget* parent)
			: QTreeWidgetItem(parent)
			, m_MeshLineEdit(nullptr)
			, m_WidgetWrapper(nullptr)
			, m_Entity(nullptr) {
			m_WidgetWrapper = new QTreeWidgetItem(this);
			m_MeshLineEdit = new QLineEdit(parent);

			setText(0, "Mesh");
			addChild(m_WidgetWrapper);

			InitConnections();
		}

		void MeshComponentWidgetItem::OnLineEditPress() {
			QString& text{ m_MeshLineEdit->text() };

			if (m_Entity && !m_Entity->IsNull()) {
				std::string& name{ m_Entity->GetComponent<pawn::engine::MeshComponent>().MeshName };
				name = text.toLocal8Bit().constData();
			}

			emit EntityMeshModified(*m_Entity);
			m_MeshLineEdit->clearFocus();
		}

		void MeshComponentWidgetItem::InitConnections() {
			connect(
				m_MeshLineEdit,
				SIGNAL(returnPressed()),
				SLOT(OnLineEditPress())
			);
		}

	}

}
