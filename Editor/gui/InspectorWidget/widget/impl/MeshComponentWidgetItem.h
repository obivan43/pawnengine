#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QLineEdit>

namespace editor {

	namespace impl {

		class MeshComponentWidgetItem : public QObject, public QTreeWidgetItem {
				Q_OBJECT

			public:
				MeshComponentWidgetItem(QTreeWidget* parent);

				void SetEntity(pawn::engine::GameEntity* entity) { m_Entity = entity; }

				QLineEdit* GetWidget() { return m_MeshLineEdit; }
				QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

			private:
				void InitConnections();

			public slots:
				void OnLineEditPress();

			signals:
				void EntityMeshModified(pawn::engine::GameEntity entity);

			private:
				QLineEdit* m_MeshLineEdit;
				QTreeWidgetItem* m_WidgetWrapper;
				pawn::engine::GameEntity* m_Entity;
		};

	}

}
