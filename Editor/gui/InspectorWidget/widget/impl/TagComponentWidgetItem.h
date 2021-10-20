#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include "TagComponentWidget.h"

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QLineEdit>

namespace editor::impl {

	class TagComponentWidgetItem : public QObject, public QTreeWidgetItem {
			Q_OBJECT

		public:
			TagComponentWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::engine::GameEntity* entity);

			TagComponentWidget* GetWidget() { return m_TagComponentWidget; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			void InitConnections();

		signals:
			void EntityTagModified();

		private:
			TagComponentWidget* m_TagComponentWidget;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::engine::GameEntity* m_Entity;
	};

}
