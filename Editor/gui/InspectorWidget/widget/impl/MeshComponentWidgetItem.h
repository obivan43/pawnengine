#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include "MeshComponentWidget.h"

#include <QtWidgets/QTreeWidgetItem>

namespace editor::impl {

	class MeshComponentWidgetItem : public QObject, public QTreeWidgetItem {
			Q_OBJECT

		public:
			MeshComponentWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::engine::GameEntity* entity);

			MeshComponentWidget* GetWidget() { return m_MeshComponentWidget; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			void InitConnections();

		signals:
			void EntityMeshModified(pawn::engine::GameEntity entity);

		private:
			MeshComponentWidget* m_MeshComponentWidget;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::engine::GameEntity* m_Entity;
	};

}
