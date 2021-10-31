#pragma once

#include "Editor/gui/CommonWidgets/widgets/Double3Widget.h"
#include "Editor/gui/CommonWidgets/widgets/DoubleLabelWidget.h"

#include "PawnEngine/engine/components/DirectionalLightComponent.h"

#include <QtWidgets/QWidget>

namespace editor::impl {

		class DirectionalLightWidget : public QWidget {
			Q_OBJECT

			public:
				DirectionalLightWidget(QWidget* parent = Q_NULLPTR);

				void SetDirectionalLight(pawn::engine::DirectionalLightComponent* directionalLight);

			private slots:
				void OnAmbientChanged(glm::vec3);
				void OnDeffuseChanged(glm::vec3);
				void OnSpecularChanged(glm::vec3);
				void OnDirectionChanged(glm::vec3);

				void OnAmbientIntensityChanged(double);
				void OnDeffuseIntensityChanged(double);
				void OnSpecularIntensityChanged(double);

			private:
				void InitConnections();

			private:
				pawn::engine::DirectionalLightComponent* m_DirectionalLight;
				Double3Widget* m_Ambient;
				Double3Widget* m_Diffuse;
				Double3Widget* m_Specular;
				Double3Widget* m_Direction;

				DoubleLabelWidget* m_AmbientIntensity;
				DoubleLabelWidget* m_DiffuseIntensity;
				DoubleLabelWidget* m_SpecularIntensity;
		};


}