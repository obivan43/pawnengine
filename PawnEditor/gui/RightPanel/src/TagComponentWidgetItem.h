#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QLineEdit>

namespace impl {

	class TagComponentWidgetItem : public QObject, public QTreeWidgetItem {
		Q_OBJECT

		public:
			TagComponentWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::GameEntity* entity) { m_Entity = entity; }

			QLineEdit* GetWidget() { return m_TagLineEdit; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			void InitConnections();

		public slots:
			void OnLineEditPress();

		signals:
			void EntityTagModified();

		private:
			QLineEdit* m_TagLineEdit;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::GameEntity* m_Entity;
	};

}
