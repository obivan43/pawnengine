#pragma once

#include "PawnEngine/engine/components/CameraComponent.h"

#include <QtWidgets/QWidget>

namespace editor {

	namespace impl {

		class CameraComponentWidget : public QWidget {
			Q_OBJECT

			public:
				CameraComponentWidget(QWidget* parent = Q_NULLPTR);

				void SetCamera(pawn::engine::CameraComponent* camera);

			private:
				pawn::engine::CameraComponent* m_Camera;
		};

	}

}
