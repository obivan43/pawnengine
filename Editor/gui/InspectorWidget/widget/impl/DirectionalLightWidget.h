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