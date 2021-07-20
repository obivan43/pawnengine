#include "HierarchyWidgetImpl.h"
#include "HierarchyWidgetItem.h"

#include "PawnEngine/engine/components/TagComponent.h"

#include <QHBoxLayout>

namespace editor {

	namespace impl {

		HierarchyWidgetImpl::HierarchyWidgetImpl(QWidget* parent) : HierarchyWidget(parent) {
			m_HierarchyPanel = new QTreeWidget(this);
			m_HierarchyPanel->setHeaderHidden(true);
			m_HierarchyPanel->setSelectionMode(QAbstractItemView::NoSelection);
			m_HierarchyPanel->setFocusPolicy(Qt::NoFocus);

			QHBoxLayout* layout = new QHBoxLayout(this);
			layout->addWidget(m_HierarchyPanel);
			setLayout(layout);

			InitConnections();
		}

		void HierarchyWidgetImpl::RefreshPanel() {
			m_HierarchyPanel->clear();
			InitHierarchyPanel();
			m_HierarchyPanel->expandAll();
		}

		void HierarchyWidgetImpl::OnActiveSceneChanged(std::shared_ptr<pawn::engine::GameScene> scene) {
			if (m_Scene.get() != scene.get()) {
				m_Scene = scene;
				InitHierarchyPanel();
			}
		}

		void HierarchyWidgetImpl::InitHierarchyPanel() {
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

		void HierarchyWidgetImpl::OnHierarchyItemClicked(QTreeWidgetItem* item, int index) {
			HierarchyWidgetItem* hierarchyWidgetItem{ reinterpret_cast<HierarchyWidgetItem*>(item) };
			m_SelectedEntity = hierarchyWidgetItem->GetEntity();
			emit HierarchyWidget::SelectedEntityChanged(m_SelectedEntity);
		}

		void HierarchyWidgetImpl::InitConnections() {
			connect(
				m_HierarchyPanel,
				SIGNAL(itemClicked(QTreeWidgetItem*, int)),
				this,
				SLOT(OnHierarchyItemClicked(QTreeWidgetItem*, int))
			);
		}

		void HierarchyWidgetImpl::OnEntityTagModified() {
			RefreshPanel();
		}

	}

}
