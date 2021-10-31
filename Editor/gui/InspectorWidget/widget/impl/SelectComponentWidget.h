#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include <QDialog>
#include <QListWidget>

namespace editor::impl {

	enum class ComponentsEnum {
		MeshComponent,
		ScriptComponent,
		CameraComponent,
		Texture2DComponent,
		DirectionalLightComponent,
		Unknown
	};

	class SelectComponentWidget : public QDialog {
		Q_OBJECT

		public:
			SelectComponentWidget(QWidget* parent = Q_NULLPTR);

			void Update();
			void SetEntity(pawn::engine::GameEntity* entity);

			QListView* GetListView() { return m_ListWidget; }

		signals:
			void AddedNewComponent(ComponentsEnum id);

		public slots:
			void OnClicked(QListWidgetItem*);

		private:
			void InitConnections();

		private:
			pawn::engine::GameEntity* m_Entity;

			QListWidget* m_ListWidget;
	};

}
