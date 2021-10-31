#include "SelectComponentWidget.h"

#include "PawnEngine/engine/components/MeshComponent.h"
#include "PawnEngine/engine/components/ScriptComponent.h"
#include "PawnEngine/engine/components/CameraComponent.h"
#include "PawnEngine/engine/components/Texture2DComponent.h"
#include "PawnEngine/engine/components/DirectionalLightComponent.h"

#include <QVBoxLayout>

namespace editor::impl {

	SelectComponentWidget::SelectComponentWidget(QWidget* parent)
		: QDialog(parent)
		, m_ListWidget(nullptr) {

		QVBoxLayout* layout = new QVBoxLayout();

		m_ListWidget = new QListWidget();

		layout->addWidget(m_ListWidget);

		setLayout(layout);

		InitConnections();
	}

	void SelectComponentWidget::Update() {
		QStringList componentsList;

		if (!m_Entity->HasComponent<pawn::engine::MeshComponent>()) {
			componentsList.append("MeshCompnent");
		}

		if (!m_Entity->HasComponent<pawn::engine::ScriptComponent>()) {
			componentsList.append("ScriptComponent");
		}

		if (!m_Entity->HasComponent<pawn::engine::CameraComponent>()) {
			componentsList.append("CameraComponent");
		}

		if (!m_Entity->HasComponent<pawn::engine::Texture2DComponent>()) {
			componentsList.append("Texture2DComponent");
		}

		if (!m_Entity->HasComponent<pawn::engine::DirectionalLightComponent>()) {
			componentsList.append("DirectionalLightComponent");
		}

		m_ListWidget->clear();
		m_ListWidget->addItems(componentsList);
	}

	void SelectComponentWidget::SetEntity(pawn::engine::GameEntity* entity) {
		m_Entity = entity;
	}

	void SelectComponentWidget::OnClicked(QListWidgetItem* item) {
		if (m_Entity == nullptr || m_Entity->IsNull()) {
			return;
		}

		static QHash<QString, ComponentsEnum> componentsTable{
			{ "MeshCompnent", ComponentsEnum::MeshComponent },
			{ "ScriptComponent", ComponentsEnum::ScriptComponent },
			{ "CameraComponent", ComponentsEnum::CameraComponent },
			{ "Texture2DComponent", ComponentsEnum::Texture2DComponent },
			{ "DirectionalLightComponent", ComponentsEnum::DirectionalLightComponent }
		};

		ComponentsEnum componentID{ ComponentsEnum::Unknown };
		const QString& selectedText = item->text();
		switch (componentsTable[selectedText]) {
			case ComponentsEnum::MeshComponent:
				m_Entity->AddComponent<pawn::engine::MeshComponent>();
				componentID = ComponentsEnum::MeshComponent;
				break;
			case ComponentsEnum::ScriptComponent:
				m_Entity->AddComponent<pawn::engine::ScriptComponent>();
				componentID = ComponentsEnum::ScriptComponent;
				break;
			case ComponentsEnum::CameraComponent:
				m_Entity->AddComponent<pawn::engine::CameraComponent>();
				componentID = ComponentsEnum::CameraComponent;
				break;
			case ComponentsEnum::Texture2DComponent:
				m_Entity->AddComponent<pawn::engine::Texture2DComponent>();
				componentID = ComponentsEnum::Texture2DComponent;
				break;
			case ComponentsEnum::DirectionalLightComponent:
				m_Entity->AddComponent<pawn::engine::DirectionalLightComponent>();
				componentID = ComponentsEnum::DirectionalLightComponent;
				break;
		}

		close();

		emit AddedNewComponent(componentID);
	}

	void SelectComponentWidget::InitConnections() {
		connect(
			m_ListWidget,
			SIGNAL(itemDoubleClicked(QListWidgetItem*)),
			this,
			SLOT(OnClicked(QListWidgetItem*))
		);
	}

}