#include "HierarchyWidgetImpl.h"
#include "HierarchyWidgetItem.h"

#include "PawnEngine/engine/components/TagComponent.h"
#include "PawnEngine/engine/components/MeshComponent.h"

#include <QHBoxLayout>

namespace editor {

	namespace impl {

		HierarchyWidgetImpl::HierarchyWidgetImpl(QWidget* parent)
			: HierarchyWidget(parent)
			, m_HierarchyPanel(nullptr) {

			m_HierarchyPanel = new QTreeWidget(this);
			m_HierarchyPanel->setHeaderHidden(true);
			m_HierarchyPanel->setFocusPolicy(Qt::NoFocus);

			setContextMenuPolicy(Qt::CustomContextMenu);

			m_ContextMenu = new HierarchyWidgetContextMenu(this);

			QHBoxLayout* layout = new QHBoxLayout(this);
			layout->addWidget(m_HierarchyPanel);
			setLayout(layout);

			InitConnections();
		}

		void HierarchyWidgetImpl::RefreshPanel() {
			m_HierarchyPanel->clear();

			InitHierarchyPanel();
			FindEntityToSelect(m_HierarchyPanel->invisibleRootItem());

			m_HierarchyPanel->expandAll();
		}

		void HierarchyWidgetImpl::SetSelectedEntity(pawn::engine::GameEntity entity) {
			m_SelectedEntity = entity;
			emit HierarchyWidget::SelectedEntityChanged(m_SelectedEntity);
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

		void HierarchyWidgetImpl::ShowContextMenu(const QPoint& position) {
			m_ContextMenu->ShowMenu(this, position);
		}

		void HierarchyWidgetImpl::InitConnections() {
			connect(
				m_HierarchyPanel,
				SIGNAL(itemClicked(QTreeWidgetItem*, int)),
				this,
				SLOT(OnHierarchyItemClicked(QTreeWidgetItem*, int))
			);

			connect(
				this, 
				SIGNAL(customContextMenuRequested(const QPoint&)),
				SLOT(ShowContextMenu(const QPoint&))
			);
		}

		void HierarchyWidgetImpl::OnEntityTagModified() {
			RefreshPanel();
		}

		bool HierarchyWidgetImpl::FindEntityToSelect(QTreeWidgetItem* item) {
			if (!m_SelectedEntity.IsNull()) {
				HierarchyWidgetItem* hierarchyWidgetItem{ reinterpret_cast<HierarchyWidgetItem*>(item) };
				if (hierarchyWidgetItem->GetEntity() == m_SelectedEntity) {
					hierarchyWidgetItem->setSelected(true);
					emit HierarchyWidget::SelectedEntityChanged(m_SelectedEntity);
					return true;
				}

				bool result{ false };
				for (uint i{ 0 }; i < item->childCount(); ++i) {
					result = FindEntityToSelect(item->child(i));

					if (result) {
						return true;
					}
				}
			}
			return false;
		}

	}

}
