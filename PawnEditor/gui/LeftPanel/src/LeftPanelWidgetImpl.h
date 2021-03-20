#pragma once

#include "LeftPanelWidget.h"

#include <QtWidgets/QTreeWidget>
#include <memory>

namespace impl {

	class LeftPanelWidgetImpl : public LeftPanelWidget {
			Q_OBJECT

		public:
			LeftPanelWidgetImpl(QWidget* parent);

			void RefreshPanel();

			std::shared_ptr<pawn::Scene>& GetScene() { return m_Scene; }
			pawn::Entity& GetSelectedEntity() { return m_SelectedEntity; }

		private:
			void InitHierarchyPanel();
			void InitConnections();

		public slots:
			void OnHierarchyItemClicked(QTreeWidgetItem* item, int index);
			void OnActiveSceneChanged(std::shared_ptr<pawn::Scene> scene);
			void OnEntityModified();

		private:
			std::shared_ptr<pawn::Scene> m_Scene;
			pawn::Entity m_SelectedEntity;

			QTreeWidget* m_HierarchyPanel;
	};

}
