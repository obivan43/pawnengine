#pragma once

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QLineEdit>

namespace impl {

	class TagComponentWidgetItem : public QObject, public QTreeWidgetItem {
		Q_OBJECT

		public:
			TagComponentWidgetItem(QTreeWidget* parent);
			TagComponentWidgetItem(QTreeWidget* parent, pawn::Entity* entity);

			void SetEntity(pawn::Entity* entity) { m_Entity = entity; }

			QLineEdit* GetTagComponentWidget() { return m_TagLineEdit; }
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
			pawn::Entity* m_Entity;
	};

}
