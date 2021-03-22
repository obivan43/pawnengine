#pragma once

#include "Double3Widget.h"

#include <QtWidgets/QWidget>

namespace impl {

	class TransformationComponentWidget : public QWidget {
		Q_OBJECT

		public:
			TransformationComponentWidget(QWidget* parent = Q_NULLPTR);
			TransformationComponentWidget(pawn::TransformationComponent* transformation, QWidget* parent = Q_NULLPTR);

			void SetTransformation(pawn::TransformationComponent* transformation);

			QSize sizeHint() const override;

		private slots:
			void OnPositionChanged(glm::vec3);

		private:
			void InitConnections();

		private:
			pawn::TransformationComponent* m_Transformation;
			Double3Widget* m_Position;
	};

}
