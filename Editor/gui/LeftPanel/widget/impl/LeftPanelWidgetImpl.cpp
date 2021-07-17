#include "LeftPanelWidgetImpl.h"
#include "HierarchyWidgetItem.h"

#include "PawnEngine/engine/components/TagComponent.h"

namespace editor {

	namespace impl {

		LeftPanelWidgetImpl::LeftPanelWidgetImpl(QWidget* parent) : LeftPanelWidget(parent) {
			m_HierarchyPanel = new QTreeWidget(this);
			m_HierarchyPanel->setHeaderHidden(true);

			setWindowTitle("Scene Hierarchy");
			setWidget(m_HierarchyPanel);

			InitConnections();
		}

		void LeftPanelWidgetImpl::RefreshPanel() {
			m_HierarchyPanel->clear();
			InitHierarchyPanel();
			m_HierarchyPanel->expandAll();
		}

		void LeftPanelWidgetImpl::OnActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene> scene) {
			if (m_Scene.get() != scene.get()) {
				m_Scene = scene;
				InitHierarchyPanel();
			}
		}

		void LeftPanelWidgetImpl::InitHierarchyPanel() {
			entt::registry& registry{ m_Scene->GetRegistry() };

			HierarchyWidgetItem* root = new HierarchyWidgetItem(pawn::engine::GameEntity(), "Scene");
			m_HierarchyPanel->addTopLevelItem(root);

			registry.each([&](auto entityID) {
				pawn::engine::GameEntity entity{ entityID, m_Scene.get() };
				std::string& tag{ entity.GetComponent<pawn::engine::TagComponent>().Tag };

				HierarchyWidgetItem* item = new HierarchyWidgetItem(entity, tag.c_str(), root);
				root->addChild(reinterpret_cast<QTreeWidgetItem*>(item));
			});
		}

		void LeftPanelWidgetImpl::OnHierarchyItemClicked(QTreeWidgetItem* item, int index) {
			HierarchyWidgetItem* hierarchyWidgetItem{ reinterpret_cast<HierarchyWidgetItem*>(item) };
			m_SelectedEntity = hierarchyWidgetItem->GetEntity();
			emit LeftPanelWidget::SelectedEntityChanged(m_SelectedEntity);
		}

		void LeftPanelWidgetImpl::InitConnections() {
			connect(
				m_HierarchyPanel,
				SIGNAL(itemClicked(QTreeWidgetItem*, int)),
				this,
				SLOT(OnHierarchyItemClicked(QTreeWidgetItem*, int))
			);
		}

		void LeftPanelWidgetImpl::OnEntityTagModified() {
			RefreshPanel();
		}

	}

}
