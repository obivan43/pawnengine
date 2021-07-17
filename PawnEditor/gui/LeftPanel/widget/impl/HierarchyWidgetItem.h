#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include <QtWidgets/QTreeWidgetItem>

namespace impl {

	class HierarchyWidgetItem : public QTreeWidgetItem {

		public:
			HierarchyWidgetItem(pawn::engine::GameEntity entity, const QString& str, QTreeWidgetItem* parent = Q_NULLPTR);

			pawn::engine::GameEntity GetEntity() const { return m_Entity; }

		private:
			pawn::engine::GameEntity m_Entity;
	};

}
