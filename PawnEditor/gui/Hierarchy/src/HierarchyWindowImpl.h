#pragma once

#include "HierarchyWindow.h"

#include <QtWidgets/QTreeWidget>
#include <memory>

namespace impl {

	class HierarchyWindowImpl : public HierarchyWindow {
			Q_OBJECT

		public:
			HierarchyWindowImpl(std::shared_ptr<pawn::Scene>& scene, QWidget* parent);

			void RefreshPanel();

			std::shared_ptr<pawn::Scene>& GetScene() { return m_Scene; }
			pawn::Entity& GetSelectedEntity() { return m_SelectedEntity; }

		private:
			void InitHierarchyPanel();
			void InitConnections();

		public slots:
			void OnHierarchyItemClicked(QTreeWidgetItem* item, int index);

		private:
			std::shared_ptr<pawn::Scene> m_Scene;
			pawn::Entity m_SelectedEntity;

			QTreeWidget* m_HierarchyPanel;
	};

}
