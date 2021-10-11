#pragma once

#include "Editor/gui/HierarchyWidget/widget/HierarchyWidget.h"
#include "HierarchyWidgetContextMenu.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/GameScene.h"

#include <QtWidgets/QTreeWidget>

#include <memory>

namespace editor {

	namespace impl {

		class HierarchyWidgetImpl : public HierarchyWidget {
				Q_OBJECT

			public:
				HierarchyWidgetImpl(QWidget* parent);

				void RefreshPanel() override;

				void SetSelectedEntity(pawn::engine::GameEntity entity);

				std::shared_ptr<pawn::engine::GameScene>& GetScene() { return m_Scene; }
				pawn::engine::GameEntity& GetSelectedEntity() { return m_SelectedEntity; }

			private:
				void InitHierarchyPanel();
				void InitConnections();

				bool FindEntityToSelect(QTreeWidgetItem* item);

			public slots:
				void OnHierarchyItemClicked(QTreeWidgetItem* item, int index);
				void OnActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene> scene);
				void OnEntityTagModified();

				void ShowContextMenu(const QPoint& position);

			private:
				std::shared_ptr<pawn::engine::GameScene> m_Scene;
				pawn::engine::GameEntity m_SelectedEntity;

				HierarchyWidgetContextMenu* m_ContextMenu;

				QTreeWidget* m_HierarchyPanel;
		};

	}

}
