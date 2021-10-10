#include "SelectComponentWidget.h"

#include "PawnEngine/engine/components/MeshComponent.h"
#include "PawnEngine/engine/components/ScriptComponent.h"
#include "PawnEngine/engine/components/CameraComponent.h"

#include <QVBoxLayout>

namespace editor {

	namespace impl {

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

			static QHash<QString, ComponentsEnum> componentsTable {
				{ "MeshCompnent", ComponentsEnum::MeshComponent },
				{ "ScriptComponent", ComponentsEnum::ScriptComponent },
				{ "CameraComponent", ComponentsEnum::CameraComponeent }
			};

			const QString& selectedText = item->text();
			switch (componentsTable[selectedText]) {
				case ComponentsEnum::MeshComponent:
					m_Entity->AddComponent<pawn::engine::MeshComponent>();
					break;
				case ComponentsEnum::ScriptComponent:
					m_Entity->AddComponent<pawn::engine::ScriptComponent>();
					break;
				case ComponentsEnum::CameraComponeent:
					m_Entity->AddComponent<pawn::engine::CameraComponent>();
					break;
			}

			close();

			emit AddedNewComponent();
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

}