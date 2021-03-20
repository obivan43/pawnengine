#include "pch.h"
#include "HierarchyWidgetItem.h"

namespace impl {

	HierarchyWidgetItem::HierarchyWidgetItem(pawn::Entity entity, const QString& str, QTreeWidgetItem* parent)
		: QTreeWidgetItem(parent), m_Entity(entity) {
		setText(0, str);
	}

}