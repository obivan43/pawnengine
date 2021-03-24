#pragma once

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QLineEdit>

namespace impl {

	class MeshComponentWidgetItem : public QObject, public QTreeWidgetItem {
		Q_OBJECT

		public:
			MeshComponentWidgetItem(QTreeWidget* parent);

			void SetEntity(pawn::Entity* entity) { m_Entity = entity; }

			QLineEdit* GetWidget() { return m_MeshLineEdit; }
			QTreeWidgetItem* GetWrapper() { return m_WidgetWrapper; }

		private:
			void InitConnections();

		public slots:
			void OnLineEditPress();

		signals:
			void EntityMeshModified(pawn::Entity entity);

		private:
			QLineEdit* m_MeshLineEdit;
			QTreeWidgetItem* m_WidgetWrapper;
			pawn::Entity* m_Entity;
	};

}