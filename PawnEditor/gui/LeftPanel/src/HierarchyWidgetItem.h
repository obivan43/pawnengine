#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include <QtWidgets/QTreeWidgetItem>

namespace impl {

	class HierarchyWidgetItem : public QTreeWidgetItem {

		public:
			HierarchyWidgetItem(pawn::GameEntity entity, const QString& str, QTreeWidgetItem* parent = Q_NULLPTR);

			pawn::GameEntity GetEntity() const { return m_Entity; }

		private:
			pawn::GameEntity m_Entity;
	};

}
