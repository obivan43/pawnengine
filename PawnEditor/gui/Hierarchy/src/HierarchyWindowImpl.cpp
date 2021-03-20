#include "pch.h"
#include "HierarchyWindowImpl.h"
#include "HierarchyWidgetItem.h"

namespace impl {

	HierarchyWindowImpl::HierarchyWindowImpl(std::shared_ptr<pawn::Scene>& scene, QWidget* parent) : HierarchyWindow(parent), m_Scene(scene) {
		m_HierarchyPanel = new QTreeWidget(this);
		m_HierarchyPanel->setHeaderHidden(true);

		setWindowTitle("Scene Hierarchy");
		setWidget(m_HierarchyPanel);

		InitHierarchyPanel();
		InitConnections();
	}

	void HierarchyWindowImpl::RefreshPanel() {
		m_HierarchyPanel->clear();
		InitHierarchyPanel();
		m_HierarchyPanel->expandAll();
	}

	void HierarchyWindowImpl::InitHierarchyPanel() {
		entt::registry& registry = m_Scene->GetRegistry();

		HierarchyWidgetItem* root = new HierarchyWidgetItem(pawn::Entity(), "Scene");
		m_HierarchyPanel->addTopLevelItem(root);

		registry.each([&](auto entityID) {
			pawn::Entity entity(entityID, m_Scene.get());
			std::string& name = entity.GetComponent<pawn::NameComponent>().m_Name;

			HierarchyWidgetItem* item = new HierarchyWidgetItem(entity, name.c_str(), root);
			root->addChild((QTreeWidgetItem*)item);
		});
	}

	void HierarchyWindowImpl::OnHierarchyItemClicked(QTreeWidgetItem* item, int index) {
		HierarchyWidgetItem* hierarchyWidgetItem = reinterpret_cast<HierarchyWidgetItem*>(item);
		m_SelectedEntity = hierarchyWidgetItem->GetEntity();
		emit HierarchyWindow::SelectedEntityChanged(m_SelectedEntity);
	}

	void HierarchyWindowImpl::InitConnections() {
		connect(
			m_HierarchyPanel,
			SIGNAL(itemClicked(QTreeWidgetItem*, int)),
			this,
			SLOT(OnHierarchyItemClicked(QTreeWidgetItem*, int))
		);
	}

}
