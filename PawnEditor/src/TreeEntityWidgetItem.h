#pragma once

#include <QtWidgets/QTreeWidgetItem>

class TreeEntityWidgetItem : public QTreeWidgetItem {

	public:
		TreeEntityWidgetItem(pawn::Entity entity, const QString& str, QTreeWidgetItem* parent = Q_NULLPTR);

		pawn::Entity GetEntity() const { return m_Entity; }

	private:
		pawn::Entity m_Entity;
};
