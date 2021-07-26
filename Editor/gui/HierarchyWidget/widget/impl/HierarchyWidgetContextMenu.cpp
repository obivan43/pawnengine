#include "HierarchyWidgetContextMenu.h"

#include "Editor/editor/impl/EngineManager.h"

#include "Editor/gui/HierarchyWidget/widget/impl/HierarchyWidgetImpl.h"

#include "PawnEngine/engine/GameScene.h"
#include "PawnEngine/engine/components/MeshComponent.h"

namespace editor {

	namespace impl {

		HierarchyWidgetContextMenu::HierarchyWidgetContextMenu(QWidget* parent)
			: m_ContextMenu(nullptr)
			, m_CreateEmptyEntity(nullptr)
			, m_DeleteEntity(nullptr)
			, m_Create3DObject(nullptr)
			, m_CreateCube(nullptr)
			, m_CreateSphere(nullptr)
			, m_CreateCone(nullptr)
			, m_CreateTorus(nullptr)
			, m_CreateCylinder(nullptr) {

			m_ContextMenu = new QMenu("Context menu", parent);
			m_CreateEmptyEntity = new QAction("Create empty", m_ContextMenu);
			m_DeleteEntity = new QAction("Delete", m_ContextMenu);

			m_Create3DObject = new QMenu("3D Object", m_ContextMenu);
			m_CreateCube = new QAction("Cube", m_ContextMenu);
			m_CreateSphere = new QAction("Sphere", m_ContextMenu);
			m_CreateCone = new QAction("Cone", m_ContextMenu);
			m_CreateTorus = new QAction("Torus", m_ContextMenu);
			m_CreateCylinder = new QAction("Cylinder", m_ContextMenu);

			m_Create3DObject->addAction(m_CreateCube);
			m_Create3DObject->addAction(m_CreateSphere);
			m_Create3DObject->addAction(m_CreateCone);
			m_Create3DObject->addAction(m_CreateTorus);
			m_Create3DObject->addAction(m_CreateCylinder);

			m_ContextMenu->addAction(m_DeleteEntity);
			m_ContextMenu->addSeparator();
			m_ContextMenu->addAction(m_CreateEmptyEntity);
			m_ContextMenu->addMenu(m_Create3DObject);

			InitConnections();
		}

		void HierarchyWidgetContextMenu::ShowMenu(
			HierarchyWidgetImpl* widget,
			const QPoint& position
		) {
			m_HierarchyWidget = widget;
			m_ContextMenu->exec(m_HierarchyWidget->mapToGlobal(position));
		}

		void HierarchyWidgetContextMenu::CreateEmptyEntity() {
			std::shared_ptr<pawn::engine::GameScene> scene = m_HierarchyWidget->GetScene();

			if (m_HierarchyWidget && scene) {
				pawn::engine::GameEntity entity = scene->CreateEntity();

				m_HierarchyWidget->SetSelectedEntity(entity);
				m_HierarchyWidget->RefreshPanel();
			}
		}

		pawn::engine::GameEntity HierarchyWidgetContextMenu::Create3DObject(const QString& name) {
			std::string objectName = name.toLocal8Bit().constData();
			std::shared_ptr<pawn::engine::GameScene> scene = m_HierarchyWidget->GetScene();
			EngineManager* manager = m_HierarchyWidget->GetEngineManager();

			if (m_HierarchyWidget && scene) {
				pawn::engine::GameEntity entity{ scene->CreateEntity(objectName) };
				entity.AddComponent<pawn::engine::MeshComponent>(
					manager->GetEngine()->GetMeshByName(objectName + ".obj"),
					objectName + ".obj"
				);

				return entity;
			}

			return pawn::engine::GameEntity();
		}

		void HierarchyWidgetContextMenu::CreateCube() {
			pawn::engine::GameEntity entity = Create3DObject("cube");

			m_HierarchyWidget->SetSelectedEntity(entity);
			m_HierarchyWidget->RefreshPanel();
		}

		void HierarchyWidgetContextMenu::CreateSphere() {
			pawn::engine::GameEntity entity = Create3DObject("sphere");

			m_HierarchyWidget->SetSelectedEntity(entity);
			m_HierarchyWidget->RefreshPanel();
		}

		void HierarchyWidgetContextMenu::CreateCone() {
			pawn::engine::GameEntity entity = Create3DObject("cone");

			m_HierarchyWidget->SetSelectedEntity(entity);
			m_HierarchyWidget->RefreshPanel();
		}

		void HierarchyWidgetContextMenu::CreateTorus() {
			pawn::engine::GameEntity entity = Create3DObject("torus");

			m_HierarchyWidget->SetSelectedEntity(entity);
			m_HierarchyWidget->RefreshPanel();
		}

		void HierarchyWidgetContextMenu::CreateCylinder() {
			pawn::engine::GameEntity entity = Create3DObject("cylinder");

			m_HierarchyWidget->SetSelectedEntity(entity);
			m_HierarchyWidget->RefreshPanel();
		}

		void HierarchyWidgetContextMenu::DeleteEntity() {
			std::shared_ptr<pawn::engine::GameScene> scene = m_HierarchyWidget->GetScene();
			pawn::engine::GameEntity selectedEntity = m_HierarchyWidget->GetSelectedEntity();

			if (m_HierarchyWidget && !selectedEntity.IsNull() && scene) {
				scene->DeleteEntity(selectedEntity.GetEntity());

				m_HierarchyWidget->SetSelectedEntity(pawn::engine::GameEntity());
				m_HierarchyWidget->RefreshPanel();
			}
		}

		void HierarchyWidgetContextMenu::InitConnections() {
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

	}

}
