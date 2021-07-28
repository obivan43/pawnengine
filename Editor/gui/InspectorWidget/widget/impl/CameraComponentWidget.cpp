#include "CameraComponentWidget.h"

namespace editor {

	namespace impl {

		CameraComponentWidget::CameraComponentWidget(QWidget* parent)
			: QWidget(parent)
			, m_Camera(nullptr) {

		}

		void CameraComponentWidget::SetCamera(pawn::engine::CameraComponent* camera) {
			m_Camera = camera;
		}

	}

}