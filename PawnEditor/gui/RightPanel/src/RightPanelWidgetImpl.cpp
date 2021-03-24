#include "pch.h"
#include "RightPanelWidgetImpl.h"

namespace impl {

	RightPanelWidgetImpl::RightPanelWidgetImpl(QWidget* parent) : RightPanelWidget(parent) {
		m_InspectorPanel = new QTreeWidget(this);
		m_InspectorPanel->setHeaderHidden(true);

		setWindowTitle("Inspector");
		setWidget(m_InspectorPanel);

		InitTagComponent();
		InitTransformationComponent();
		InitMeshComponent();
		InitConnections();
	}

	void RightPanelWidgetImpl::InitTagComponent() {
		m_TagComponentInspectorWidget = new TagComponentWidgetItem(m_InspectorPanel);
		m_TagComponentInspectorWidget->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_TagComponentInspectorWidget);
		m_InspectorPanel->setItemWidget(m_TagComponentInspectorWidget->GetWrapper(), 0, m_TagComponentInspectorWidget->GetWidget());
	}

	void RightPanelWidgetImpl::InitTransformationComponent() {
		m_TransformationComponentInspectorWidget = new TransformationComponentWidgetItem(m_InspectorPanel);
		m_TransformationComponentInspectorWidget->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_TransformationComponentInspectorWidget);
		m_InspectorPanel->setItemWidget(m_TransformationComponentInspectorWidget->GetWrapper(), 0, m_TransformationComponentInspectorWidget->GetWidget());
	}

	void RightPanelWidgetImpl::InitMeshComponent() {
		m_MeshComponentWidgetItem = new MeshComponentWidgetItem(m_InspectorPanel);
		m_MeshComponentWidgetItem->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_MeshComponentWidgetItem);
		m_InspectorPanel->setItemWidget(m_MeshComponentWidgetItem->GetWrapper(), 0, m_MeshComponentWidgetItem->GetWidget());
	}

	void RightPanelWidgetImpl::OnSelectedEntityChanged(pawn::Entity entity) {
		m_SelectedEntity = entity;
		m_TagComponentInspectorWidget->SetEntity(&m_SelectedEntity);
		m_TransformationComponentInspectorWidget->SetEntity(&m_SelectedEntity);
		m_MeshComponentWidgetItem->SetEntity(&m_SelectedEntity);
		RefreshPanel();
	}

	void RightPanelWidgetImpl::RefreshPanel() {
		if (!m_SelectedEntity.IsNull()) {
			pawn::TagComponent& tagComponent = m_SelectedEntity.GetComponent<pawn::TagComponent>();

			QLineEdit* tagLineEdit = m_TagComponentInspectorWidget->GetWidget();
			tagLineEdit->setText(tagComponent.Tag.c_str());

			m_TagComponentInspectorWidget->setHidden(false);
			m_TransformationComponentInspectorWidget->setHidden(false);

			bool IsMeshComponentExitst = m_SelectedEntity.HasComponent<pawn::MeshComponent>();
			if (IsMeshComponentExitst) {
				pawn::MeshComponent& meshComponent = m_SelectedEntity.GetComponent<pawn::MeshComponent>();

				QLineEdit* meshLineEdit = m_MeshComponentWidgetItem->GetWidget();
				meshLineEdit->setText(meshComponent.MeshPath.c_str());
			}

			m_MeshComponentWidgetItem->setHidden(!IsMeshComponentExitst);
		}
		else {
			m_TagComponentInspectorWidget->setHidden(true);
			m_TransformationComponentInspectorWidget->setHidden(true);
			m_MeshComponentWidgetItem->setHidden(true);
		}
	}

	void RightPanelWidgetImpl::InitConnections() {
		connect(
			m_TagComponentInspectorWidget,
			SIGNAL(EntityTagModified()),
			this,
			SIGNAL(EntityTagModified()),
			Qt::QueuedConnection
		);

		qRegisterMetaType<pawn::Entity>("pawn::Entity");
		connect(
			m_MeshComponentWidgetItem,
			SIGNAL(EntityMeshModified(pawn::Entity)),
			this,
			SIGNAL(EntityMeshModfied(pawn::Entity)),
			Qt::QueuedConnection
		);
	}

}
