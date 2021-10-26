#pragma once

#include "Editor/gui/CommonWidgets/widgets/Double3Widget.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/components/Texture2DComponent.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

namespace editor::impl {

	class Texture2DComponentWidget : public QWidget {
		Q_OBJECT

		public:
			Texture2DComponentWidget(QWidget* parent = Q_NULLPTR);

			void SetEntity(pawn::engine::GameEntity* entity);
			void SetTexture2D(pawn::engine::Texture2DComponent* texture2D);

			QLineEdit* GetTexture2DLineEdit() { return m_Texture2DLineEdit; }

		signals:
			void Texture2DModified(pawn::engine::GameEntity);

		public slots:
			void OnLineEditPress();
			void OnColorChanged(glm::vec3);

		private:
			void InitConnections();

		private:
			pawn::engine::GameEntity* m_Entity;
			pawn::engine::Texture2DComponent* m_Texture2D;

			Double3Widget* m_Color;
			QLineEdit* m_Texture2DLineEdit;
			QLabel* m_Texture2DLabel;
	};

}
