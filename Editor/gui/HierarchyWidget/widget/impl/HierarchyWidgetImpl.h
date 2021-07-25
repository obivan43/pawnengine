#pragma once

#include "Editor/gui/HierarchyWidget/widget/HierarchyWidget.h"

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

}