#include "pch.h"
#include "TreeEntityWidgetItem.h"

TreeEntityWidgetItem::TreeEntityWidgetItem(pawn::Entity entity, const QString& str, QTreeWidgetItem* parent)
	: QTreeWidgetItem(parent), m_Entity(entity) {
	setText(0, str);
}