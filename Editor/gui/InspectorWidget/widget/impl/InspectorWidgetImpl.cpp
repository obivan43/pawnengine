#include "InspectorWidgetImpl.h"

#include "CameraComponentWidget.h"

#include "PawnEngine/engine/components/TagComponent.h"
#include "PawnEngine/engine/components/MeshComponent.h"

#include <QVBoxLayout>
#include <QTimer>

namespace editor::impl {

	InspectorWidgetImpl::InspectorWidgetImpl(QWidget* parent) : InspectorWidget(parent) {
		m_InspectorPanel = new QTreeWidget(this);
		m_InspectorPanel->setHeaderHidden(true);
		m_InspectorPanel->setSelectionMode(QAbstractItemView::NoSelection);
		m_InspectorPanel->setFocusPolicy(Qt::NoFocus);

		InitNewComponent();

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(m_NewComponentWidget);
		layout->addWidget(m_InspectorPanel);

		setLayout(layout);

		InitTagComponent();
		InitTransformationComponent();
		InitMeshComponent();
		InitCameraComponent();
		InitScriptComponent();
		InitTexture2DComponent();
		InitDirectionalLightComponent();
		InitConnections();

		const uint32_t transfromationUpdateRate = 32;
		QTimer* timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTransformation()));
		timer->start(transfromationUpdateRate);
	}

	void InspectorWidgetImpl::InitNewComponent() {
		m_NewComponentWidget = new NewComponentWidget(this);
		m_NewComponentWidget->setHidden(true);
	}

	void InspectorWidgetImpl::InitTagComponent() {
		m_TagComponentInspectorWidgetItem = new TagComponentWidgetItem(m_InspectorPanel);
		m_TagComponentInspectorWidgetItem->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_TagComponentInspectorWidgetItem);
		m_InspectorPanel->setItemWidget(m_TagComponentInspectorWidgetItem->GetWrapper(), 0, m_TagComponentInspectorWidgetItem->GetWidget());
	}

	void InspectorWidgetImpl::InitTransformationComponent() {
		m_TransformationComponentInspectorWidgetItem = new TransformationComponentWidgetItem(m_InspectorPanel);
		m_TransformationComponentInspectorWidgetItem->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_TransformationComponentInspectorWidgetItem);
		m_InspectorPanel->setItemWidget(m_TransformationComponentInspectorWidgetItem->GetWrapper(), 0, m_TransformationComponentInspectorWidgetItem->GetWidget());
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

	void InspectorWidgetImpl::InitScriptComponent() {
		m_ScriptComponentInspectorWidgetItem = new ScriptComponentWidgetItem(m_InspectorPanel);
		m_ScriptComponentInspectorWidgetItem->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_ScriptComponentInspectorWidgetItem);
		m_InspectorPanel->setItemWidget(m_ScriptComponentInspectorWidgetItem->GetWrapper(), 0, m_ScriptComponentInspectorWidgetItem->GetWidget());
	}

	void InspectorWidgetImpl::InitTexture2DComponent() {
		m_Texture2DComponentWidgetItem = new Texture2DComponentWidgetItem(m_InspectorPanel);
		m_Texture2DComponentWidgetItem->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_Texture2DComponentWidgetItem);
		m_InspectorPanel->setItemWidget(m_Texture2DComponentWidgetItem->GetWrapper(), 0, m_Texture2DComponentWidgetItem->GetWidget());
	}

	void InspectorWidgetImpl::InitDirectionalLightComponent() {
		m_DirectionalLightComponentWidgetItem = new DirectionalLightWidgetItem(m_InspectorPanel);
		m_DirectionalLightComponentWidgetItem->setHidden(true);

		m_InspectorPanel->addTopLevelItem(m_DirectionalLightComponentWidgetItem);
		m_InspectorPanel->setItemWidget(m_DirectionalLightComponentWidgetItem->GetWrapper(), 0, m_DirectionalLightComponentWidgetItem->GetWidget());
	}

	void InspectorWidgetImpl::OnNewComponentAdded(ComponentsEnum id) {
		ForceUpdate();

		if (id == ComponentsEnum::Texture2DComponent) {
			emit EntityTexture2DModified(m_SelectedEntity);
		}
	}

	void InspectorWidgetImpl::ForceUpdate() {
		Update();
		RefreshPanel();
	}

	void InspectorWidgetImpl::OnSelectedEntityChanged(pawn::engine::GameEntity entity) {
		m_SelectedEntity = entity;
		Update();
		RefreshPanel();
	}

	void InspectorWidgetImpl::Update() {
		m_NewComponentWidget->SetEntity(&m_SelectedEntity);
		m_TagComponentInspectorWidgetItem->SetEntity(&m_SelectedEntity);
		m_TransformationComponentInspectorWidgetItem->SetEntity(&m_SelectedEntity);
		m_MeshComponentWidgetItem->SetEntity(&m_SelectedEntity);
		m_CameraComponentWidgetItem->SetEntity(&m_SelectedEntity);
		m_ScriptComponentInspectorWidgetItem->SetEntity(&m_SelectedEntity);
		m_Texture2DComponentWidgetItem->SetEntity(&m_SelectedEntity);
		m_DirectionalLightComponentWidgetItem->SetEntity(&m_SelectedEntity);
	}

	void InspectorWidgetImpl::UpdateTransformation() {
		m_TransformationComponentInspectorWidgetItem->SetEntity(&m_SelectedEntity);
	}

	void InspectorWidgetImpl::RefreshPanel() {
		if (!m_SelectedEntity.IsNull() && m_SelectedEntity.IsValid()) {
			m_NewComponentWidget->setHidden(false);
			m_TagComponentInspectorWidgetItem->setHidden(false);
			m_TransformationComponentInspectorWidgetItem->setHidden(false);

			bool IsMeshComponentExitst{ m_SelectedEntity.HasComponent<pawn::engine::MeshComponent>() };
			m_MeshComponentWidgetItem->setHidden(!IsMeshComponentExitst);

			bool IsScriptComponentExitst{ m_SelectedEntity.HasComponent<pawn::engine::ScriptComponent>() };
			m_ScriptComponentInspectorWidgetItem->setHidden(!IsScriptComponentExitst);

			bool IsCameraComponentExitst{ m_SelectedEntity.HasComponent<pawn::engine::CameraComponent>() };
			m_CameraComponentWidgetItem->setHidden(!IsCameraComponentExitst);

			bool IsTexture2DComponentExitst{ m_SelectedEntity.HasComponent<pawn::engine::Texture2DComponent>() };
			m_Texture2DComponentWidgetItem->setHidden(!IsTexture2DComponentExitst);

			bool IsDirectionalLightComponentExitst{ m_SelectedEntity.HasComponent<pawn::engine::DirectionalLightComponent>() };
			m_DirectionalLightComponentWidgetItem->setHidden(!IsDirectionalLightComponentExitst);
		}
		else {
			m_NewComponentWidget->setHidden(true);
			m_TagComponentInspectorWidgetItem->setHidden(true);
			m_TransformationComponentInspectorWidgetItem->setHidden(true);
			m_MeshComponentWidgetItem->setHidden(true);
			m_CameraComponentWidgetItem->setHidden(true);
			m_ScriptComponentInspectorWidgetItem->setHidden(true);
			m_Texture2DComponentWidgetItem->setHidden(true);
			m_DirectionalLightComponentWidgetItem->setHidden(true);
		}
	}

	void InspectorWidgetImpl::InitConnections() {
		connect(
			m_TagComponentInspectorWidgetItem,
			SIGNAL(EntityTagModified()),
			this,
			SIGNAL(EntityTagModified()),
			Qt::QueuedConnection
		);

		connect(
			m_MeshComponentWidgetItem,
			SIGNAL(EntityMeshModified(pawn::engine::GameEntity)),
			this,
			SIGNAL(EntityMeshModfied(pawn::engine::GameEntity)),
			Qt::QueuedConnection
		);

		connect(
			m_Texture2DComponentWidgetItem,
			SIGNAL(EntityTexture2DModified(pawn::engine::GameEntity)),
			this,
			SIGNAL(EntityTexture2DModified(pawn::engine::GameEntity)),
			Qt::QueuedConnection
		);

		connect(
			m_NewComponentWidget,
			SIGNAL(AddedNewComponent(ComponentsEnum)),
			this,
			SLOT(OnNewComponentAdded(ComponentsEnum))
		);
	}

}
