#include "HierarchyWidgetItem.h"

namespace impl {

	HierarchyWidgetItem::HierarchyWidgetItem(pawn::engine::GameEntity entity, const QString& str, QTreeWidgetItem* parent)
		: QTreeWidgetItem(parent), m_Entity(entity) {
		setText(0, str);
	}

}