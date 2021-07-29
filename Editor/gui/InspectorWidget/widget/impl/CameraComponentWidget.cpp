#include "CameraComponentWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace editor {

	namespace impl {

		CameraComponentWidget::CameraComponentWidget(QWidget* parent)
			: QWidget(parent)
			, m_Camera(nullptr)
			, m_Projection(nullptr)
			, m_ProjectionLabel(nullptr)
			, m_IsActiveCamera(nullptr)
			, m_IsActiveCameraLabel(nullptr) {
			QVBoxLayout* layout = new QVBoxLayout(this);

			QHBoxLayout* projectionLayout = new QHBoxLayout();

			m_Projection = new QComboBox(this);
			m_Projection->addItem("Perspective", pawn::math::CameraType::Perspective);
			m_Projection->addItem("Orthographic", pawn::math::CameraType::Orthographic);

			m_ProjectionLabel = new QLabel("Projection",this);
			m_ProjectionLabel->setMinimumWidth(80);

			projectionLayout->addWidget(m_ProjectionLabel);
			projectionLayout->addWidget(m_Projection);

			QHBoxLayout* activeCameraLayout = new QHBoxLayout();

			m_IsActiveCamera = new QCheckBox(this);

			m_IsActiveCameraLabel = new QLabel("Active camera", this);
			m_IsActiveCameraLabel->setMinimumWidth(80);

			activeCameraLayout->addWidget(m_IsActiveCameraLabel);
			activeCameraLayout->addWidget(m_IsActiveCamera);

			layout->addLayout(projectionLayout);
			layout->addLayout(activeCameraLayout);

			setLayout(layout);

			InitConnections();
		}

		void CameraComponentWidget::OnProjectionChanged(int index) {
			if (m_Camera) {
				pawn::math::Camera& camera = static_cast<pawn::math::Camera&>(*m_Camera);
				pawn::math::CameraType type = qvariant_cast<pawn::math::CameraType>(m_Projection->itemData(index));

				switch (type) {
					case pawn::math::CameraType::Perspective: {
						camera.SetPerspective();
						break;
					}

					case pawn::math::CameraType::Orthographic: {
						camera.SetOrthographic();
						break;
					}

					default:
						break;
				}
			}
		}

		void CameraComponentWidget::OnActiveCameraStateChanged(bool state) {
			if (m_Camera) {
				m_Camera->IsActiveCamera = state;
			}
		}

		void CameraComponentWidget::SetCamera(pawn::engine::CameraComponent* camera) {
			m_Camera = camera;
			if (m_Camera) {
				pawn::math::Camera& camera = static_cast<pawn::math::Camera&>(*m_Camera);
				pawn::math::CameraType type = camera.GetType();

				int index = m_Projection->findData(type);
				if (index != -1) {
					m_Projection->setCurrentIndex(index);
				}

				m_IsActiveCamera->setChecked(m_Camera->IsActiveCamera);
			}
		}

		void CameraComponentWidget::InitConnections() {
			connect(
				m_Projection,
				SIGNAL(currentIndexChanged(int)),
				this,
				SLOT(OnProjectionChanged(int))
			);

			connect(
				m_IsActiveCamera,
				SIGNAL(clicked(bool)),
				this, 
				SLOT(OnActiveCameraStateChanged(bool))
			);
		}

	}

}