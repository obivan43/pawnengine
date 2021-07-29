#include "InspectorWidgetImpl.h"

#include "CameraComponentWidget.h"

#include "PawnEngine/engine/components/TagComponent.h"
#include "PawnEngine/engine/components/MeshComponent.h"

#include <QHBoxLayout>

namespace editor {

	namespace impl {

		InspectorWidgetImpl::InspectorWidgetImpl(QWidget* parent) : InspectorWidget(parent) {
			m_InspectorPanel = new QTreeWidget(this);
			m_InspectorPanel->setHeaderHidden(true);
			m_InspectorPanel->setSelectionMode(QAbstractItemView::NoSelection);
			m_InspectorPanel->setFocusPolicy(Qt::NoFocus);

			QHBoxLayout* layout = new QHBoxLayout(this);
			layout->addWidget(m_InspectorPanel);

			setLayout(layout);

			InitTagComponent();
			InitTransformationComponent();
			InitMeshComponent();
			InitCameraComponent();
			InitConnections();
		}

		void InspectorWidgetImpl::InitTagComponent() {
			m_TagComponentInspectorWidget = new TagComponentWidgetItem(m_InspectorPanel);
			m_TagComponentInspectorWidget->setHidden(true);

			m_InspectorPanel->addTopLevelItem(m_TagComponentInspectorWidget);
			m_InspectorPanel->setItemWidget(m_TagComponentInspectorWidget->GetWrapper(), 0, m_TagComponentInspectorWidget->GetWidget());
		}

		void InspectorWidgetImpl::InitTransformationComponent() {
			m_TransformationComponentInspectorWidget = new TransformationComponentWidgetItem(m_InspectorPanel);
			m_TransformationComponentInspectorWidget->setHidden(true);

			m_InspectorPanel->addTopLevelItem(m_TransformationComponentInspectorWidget);
			m_InspectorPanel->setItemWidget(m_TransformationComponentInspectorWidget->GetWrapper(), 0, m_TransformationComponentInspectorWidget->GetWidget());
		}

		void InspectorWidgetImpl::InitMeshComponent() {
			m_MeshComponentWidgetItem = new MeshComponentWidgetItem(m_InspectorPanel);
			m_MeshComponentWidgetItem->setHidden(true);

			m_InspectorPanel->addTopLevelItem(m_MeshComponentWidgetItem);
			m_InspectorPanel->setItemWidget(m_MeshComponentWidgetItem->GetWrapper(), 0, m_MeshComponentWidgetItem->GetWidget());
		}

		void InspectorWidgetImpl::InitCameraComponent() {
			m_CameraComponentWidgetItem = new CameraComponentWidgetItem(m_InspectorPanel);
			m_CameraComponentWidgetItem->setHidden(true);

			m_InspectorPanel->addTopLevelItem(m_CameraComponentWidgetItem);
			m_InspectorPanel->setItemWidget(m_CameraComponentWidgetItem->GetWrapper(), 0, m_CameraComponentWidgetItem->GetWidget());
		}

		void InspectorWidgetImpl::OnSelectedEntityChanged(pawn::engine::GameEntity entity) {
			m_SelectedEntity = entity;
			m_TagComponentInspectorWidget->SetEntity(&m_SelectedEntity);
			m_TransformationComponentInspectorWidget->SetEntity(&m_SelectedEntity);
			m_MeshComponentWidgetItem->SetEntity(&m_SelectedEntity);
			m_CameraComponentWidgetItem->SetEntity(&m_SelectedEntity);
			RefreshPanel();
		}

		void InspectorWidgetImpl::RefreshPanel() {
			if (!m_SelectedEntity.IsNull()) {
				m_TagComponentInspectorWidget->setHidden(false);
				m_TransformationComponentInspectorWidget->setHidden(false);

				bool IsMeshComponentExitst{ m_SelectedEntity.HasComponent<pawn::engine::MeshComponent>() };
				m_MeshComponentWidgetItem->setHidden(!IsMeshComponentExitst);

				bool IsCameraComponentExitst{ m_SelectedEntity.HasComponent<pawn::engine::CameraComponent>() };
				m_CameraComponentWidgetItem->setHidden(!IsCameraComponentExitst);
			}
			else {
				m_TagComponentInspectorWidget->setHidden(true);
				m_TransformationComponentInspectorWidget->setHidden(true);
				m_MeshComponentWidgetItem->setHidden(true);
				m_CameraComponentWidgetItem->setHidden(true);
			}
		}

		void InspectorWidgetImpl::InitConnections() {
			connect(
				m_TagComponentInspectorWidget,
				SIGNAL(EntityTagModified()),
				this,
				SIGNAL(EntityTagModified()),
				Qt::QueuedConnection
			);

			qRegisterMetaType<pawn::engine::GameEntity>("pawn::engine::GameEntity");
			connect(
				m_MeshComponentWidgetItem,
				SIGNAL(EntityMeshModified(pawn::engine::GameEntity)),
				this,
				SIGNAL(EntityMeshModfied(pawn::engine::GameEntity)),
				Qt::QueuedConnection
			);
		}

	}

}
