#pragma once

#include "PawnEditor/gui/LeftPanel/widget/LeftPanelWidget.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/GameScene.h"

#include <QtWidgets/QTreeWidget>
#include <memory>

namespace impl {

	class LeftPanelWidgetImpl : public LeftPanelWidget {
			Q_OBJECT

		public:
			LeftPanelWidgetImpl(QWidget* parent);

			void RefreshPanel();

			std::shared_ptr<pawn::engine::GameScene>& GetScene() { return m_Scene; }
			pawn::engine::GameEntity& GetSelectedEntity() { return m_SelectedEntity; }

		private:
			void InitHierarchyPanel();
			void InitConnections();

		public slots:
			void OnHierarchyItemClicked(QTreeWidgetItem* item, int index);
			void OnActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene> scene);
			void OnEntityTagModified();

		private:
			std::shared_ptr<pawn::engine::GameScene> m_Scene;
			pawn::engine::GameEntity m_SelectedEntity;

			QTreeWidget* m_HierarchyPanel;
	};

}
