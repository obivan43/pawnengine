#pragma once

#include "PawnEngine/engine/GameEntity.h"

#include <QWidget>
#include <QPushButton>

namespace editor {

	namespace impl {

		class SelectComponentWidget;

		class NewComponentWidget : public QWidget {
			 Q_OBJECT

			public:
				NewComponentWidget(QWidget* parent = Q_NULLPTR);

				void SetEntity(pawn::engine::GameEntity* entity);

				QPushButton* GetButton() { return m_Button; }

			signals:
				void AddedNewComponent();

			public slots:
				void OnPress();

			private:
				void InitConnections();

			private:
				pawn::engine::GameEntity* m_Entity;

				QPushButton* m_Button;
				SelectComponentWidget* m_SelectWidget;
				
		};


	}

}
