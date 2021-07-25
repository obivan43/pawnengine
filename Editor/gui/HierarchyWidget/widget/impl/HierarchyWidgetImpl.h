#pragma once

#include "Editor/gui/HierarchyWidget/widget/HierarchyWidget.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/GameScene.h"

#include <QMenu>
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
				pawn::engine::GameEntity Create3DObject(const QString& name);

				bool FindEntityToSelect(QTreeWidgetItem* item);

			public slots:
				void OnHierarchyItemClicked(QTreeWidgetItem* item, int index);
				void OnActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene> scene);
				void OnEntityTagModified();

				void ShowContextMenu(const QPoint&);
				void CreateEmptyEntity();
				void CreateCube();
				void CreateSphere();
				void CreateCone();
				void CreateTorus();
				void CreateCylinder();

				void DeleteEntity();

			private:
				std::shared_ptr<pawn::engine::GameScene> m_Scene;
				pawn::engine::GameEntity m_SelectedEntity;

				QMenu* m_ContextMenu;
				QAction* m_CreateEmptyEntity;
				QAction* m_DeleteEntity;

				QMenu* m_Create3DObject;
				QAction* m_CreateCube;
				QAction* m_CreateSphere;
				QAction* m_CreateCone;
				QAction* m_CreateTorus;
				QAction* m_CreateCylinder;

				QTreeWidget* m_HierarchyPanel;
		};

	}

}
