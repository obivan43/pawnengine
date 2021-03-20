#include "pch.h"
#include "LeftPanelWidgetImpl.h"
#include "HierarchyWidgetItem.h"

namespace impl {

	LeftPanelWidgetImpl::LeftPanelWidgetImpl(std::shared_ptr<pawn::Scene>& scene, QWidget* parent) : LeftPanelWidget(parent), m_Scene(scene) {
		m_HierarchyPanel = new QTreeWidget(this);
		m_HierarchyPanel->setHeaderHidden(true);

		setWindowTitle("Scene Hierarchy");
		setWidget(m_HierarchyPanel);

		InitHierarchyPanel();
		InitConnections();
	}

	void LeftPanelWidgetImpl::RefreshPanel() {
		m_HierarchyPanel->clear();
		InitHierarchyPanel();
		m_HierarchyPanel->expandAll();
	}

	void LeftPanelWidgetImpl::InitHierarchyPanel() {
		entt::registry& registry = m_Scene->GetRegistry();

		HierarchyWidgetItem* root = new HierarchyWidgetItem(pawn::Entity(), "Scene");
		m_HierarchyPanel->addTopLevelItem(root);

		registry.each([&](auto entityID) {
			pawn::Entity entity(entityID, m_Scene.get());
			std::string& name = entity.GetComponent<pawn::TagComponent>().m_Name;

			HierarchyWidgetItem* item = new HierarchyWidgetItem(entity, name.c_str(), root);
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

}
