#pragma once

#include <QtWidgets/QTreeWidgetItem>

namespace impl {

	class HierarchyWidgetItem : public QTreeWidgetItem {

		public:
			HierarchyWidgetItem(pawn::Entity entity, const QString& str, QTreeWidgetItem* parent = Q_NULLPTR);

			pawn::Entity GetEntity() const { return m_Entity; }

		private:
			pawn::Entity m_Entity;
	};

}
