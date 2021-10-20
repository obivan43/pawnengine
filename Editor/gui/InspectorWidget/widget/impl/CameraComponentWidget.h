#pragma once

#include "PawnEngine/engine/components/CameraComponent.h"

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>

namespace editor::impl {

	class CameraComponentWidget : public QWidget {
		Q_OBJECT

		public:
			CameraComponentWidget(QWidget* parent = Q_NULLPTR);

			void SetCamera(pawn::engine::CameraComponent* camera);

			QComboBox* GetProjection() { return m_Projection; }
			QCheckBox* GetIsActiveCamera() { return m_IsActiveCamera; }

		private slots:
			void OnProjectionChanged(int index);
			void OnActiveCameraStateChanged(bool state);

		private:
			void InitConnections();

		private:
			pawn::engine::CameraComponent* m_Camera;

			QComboBox* m_Projection;
			QLabel* m_ProjectionLabel;

			QCheckBox* m_IsActiveCamera;
			QLabel* m_IsActiveCameraLabel;
	};

}
