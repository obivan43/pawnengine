#pragma once

#include "Double3Widget.h"

#include "PawnEngine/engine/components/TransformationComponent.h"

#include <QtWidgets/QWidget>

namespace impl {

	class TransformationComponentWidget : public QWidget {
		Q_OBJECT

		public:
			TransformationComponentWidget(QWidget* parent = Q_NULLPTR);
			TransformationComponentWidget(pawn::TransformationComponent* transformation, QWidget* parent = Q_NULLPTR);

			void SetTransformation(pawn::TransformationComponent* transformation);

		private slots:
			void OnPositionChanged(glm::vec3);
			void OnRotationChanged(glm::vec3);
			void OnScaleChanged(glm::vec3);

		private:
			void InitConnections();

		private:
			pawn::TransformationComponent* m_Transformation;
			Double3Widget* m_Position;
			Double3Widget* m_Rotation;
			Double3Widget* m_Scale;
	};

}
