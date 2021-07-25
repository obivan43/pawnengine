#include "HierarchyWidgetImpl.h"
#include "HierarchyWidgetItem.h"

#include "PawnEngine/engine/components/TagComponent.h"
#include "PawnEngine/engine/components/MeshComponent.h"

#include <QHBoxLayout>

namespace editor {

	namespace impl {

		HierarchyWidgetImpl::HierarchyWidgetImpl(QWidget* parent)
			: HierarchyWidget(parent)
			, m_HierarchyPanel(nullptr)
			, m_ContextMenu(nullptr)
			, m_CreateEmptyEntity(nullptr)
			, m_DeleteEntity(nullptr)
			, m_Create3DObject(nullptr)
			, m_CreateCube(nullptr)
			, m_CreateSphere(nullptr)
			, m_CreateCone(nullptr) 
			, m_CreateTorus(nullptr) 
			, m_CreateCylinder(nullptr) {

			m_HierarchyPanel = new QTreeWidget(this);
			m_HierarchyPanel->setHeaderHidden(true);
			m_HierarchyPanel->setFocusPolicy(Qt::NoFocus);

			setContextMenuPolicy(Qt::CustomContextMenu);

			m_ContextMenu = new QMenu("Context menu", this);
			m_CreateEmptyEntity = new QAction("Create empty", this);
			m_DeleteEntity = new QAction("Delete", this);

			m_Create3DObject = new QMenu("3D Object", this);
			m_CreateCube = new QAction("Cube", this);
			m_CreateSphere = new QAction("Sphere", this);
			m_CreateCone = new QAction("Cone", this);
			m_CreateTorus = new QAction("Torus", this);
			m_CreateCylinder = new QAction("Cylinder", this);

			m_Create3DObject->addAction(m_CreateCube);
			m_Create3DObject->addAction(m_CreateSphere);
			m_Create3DObject->addAction(m_CreateCone);
			m_Create3DObject->addAction(m_CreateTorus);
			m_Create3DObject->addAction(m_CreateCylinder);

			m_ContextMenu->addAction(m_DeleteEntity);
			m_ContextMenu->addSeparator();
			m_ContextMenu->addAction(m_CreateEmptyEntity);
			m_ContextMenu->addMenu(m_Create3DObject);

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
			m_ContextMenu->exec(mapToGlobal(position));
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

			connect(
				m_CreateEmptyEntity,
				SIGNAL(triggered()),
				this,
				SLOT(CreateEmptyEntity())
			);

			connect(
				m_CreateCube,
				SIGNAL(triggered()),
				this,
				SLOT(CreateCube())
			);

			connect(
				m_CreateSphere,
				SIGNAL(triggered()),
				this,
				SLOT(CreateSphere())
			);

			connect(
				m_CreateCone,
				SIGNAL(triggered()),
				this,
				SLOT(CreateCone())
			);

			connect(
				m_CreateTorus,
				SIGNAL(triggered()),
				this,
				SLOT(CreateTorus())
			);

			connect(
				m_CreateCylinder,
				SIGNAL(triggered()),
				this,
				SLOT(CreateCylinder())
			);

			connect(
				m_DeleteEntity,
				SIGNAL(triggered()),
				this,
				SLOT(DeleteEntity())
			);
		}

		void HierarchyWidgetImpl::CreateEmptyEntity() {
			m_Scene->CreateEntity();
			RefreshPanel();
		}

		pawn::engine::GameEntity HierarchyWidgetImpl::Create3DObject(const QString& name) {
			std::string objectName = name.toLocal8Bit().constData();
			if (m_EngineManager) {
				pawn::engine::GameEntity entity{ m_Scene->CreateEntity(objectName) };
				entity.AddComponent<pawn::engine::MeshComponent>(
					m_EngineManager->GetEngine()->GetMeshByName(objectName + ".obj"),
					objectName + ".obj"
				);

				return entity;
			}

			return pawn::engine::GameEntity();
		}

		void HierarchyWidgetImpl::CreateCube() {
			m_SelectedEntity = Create3DObject("cube");
			RefreshPanel();
		}

		void HierarchyWidgetImpl::CreateSphere() {
			m_SelectedEntity = Create3DObject("sphere");
			RefreshPanel();
		}

		void HierarchyWidgetImpl::CreateCone() {
			m_SelectedEntity = Create3DObject("cone");
			RefreshPanel();
		}

		void HierarchyWidgetImpl::CreateTorus() {
			m_SelectedEntity = Create3DObject("torus");
			RefreshPanel();
		}

		void HierarchyWidgetImpl::CreateCylinder() {
			m_SelectedEntity = Create3DObject("cylinder");
			RefreshPanel();
		}

		void HierarchyWidgetImpl::DeleteEntity() {
			if (!m_SelectedEntity.IsNull()) {
				m_Scene->DeleteEntity(m_SelectedEntity.GetEntity());
				m_SelectedEntity = pawn::engine::GameEntity();
				emit HierarchyWidget::SelectedEntityChanged(m_SelectedEntity);
				RefreshPanel();
			}
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
