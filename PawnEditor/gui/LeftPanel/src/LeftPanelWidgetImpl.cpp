#include "pch.h"
#include "LeftPanelWidgetImpl.h"
#include "HierarchyWidgetItem.h"

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

	void LeftPanelWidgetImpl::OnActiveSceneChanged(std::shared_ptr<pawn::Scene> scene) {
		if (m_Scene.get() != scene.get()) {
			m_Scene = scene;
			InitHierarchyPanel();
		}
	}

	void LeftPanelWidgetImpl::InitHierarchyPanel() {
		entt::registry& registry = m_Scene->GetRegistry();

		HierarchyWidgetItem* root = new HierarchyWidgetItem(pawn::Entity(), "Scene");
		m_HierarchyPanel->addTopLevelItem(root);

		registry.each([&](auto entityID) {
			pawn::Entity entity(entityID, m_Scene.get());
			std::string& tag = entity.GetComponent<pawn::TagComponent>().Tag;

			HierarchyWidgetItem* item = new HierarchyWidgetItem(entity, tag.c_str(), root);
			root->addChild((QTreeWidgetItem*)item);
		});
	}

	void LeftPanelWidgetImpl::OnHierarchyItemClicked(QTreeWidgetItem* item, int index) {
		HierarchyWidgetItem* hierarchyWidgetItem = reinterpret_cast<HierarchyWidgetItem*>(item);
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

	void LeftPanelWidgetImpl::OnEntityModified() {
		RefreshPanel();
	}

}
