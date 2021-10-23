#pragma once

#include "DoubleLabelWidget.h"

#include "Editor/gui/EnvironmentWidget/widget/EnvironmentWidget.h"
#include "Editor/gui/InspectorWidget/widget/impl/Double3Widget.h"

#include <QDoubleSpinBox>
#include <QLabel>
#include <QTreeWidget>
#include <QGroupBox>

namespace editor::impl {

	class EnvironmentWidgetImpl : public EnvironmentWidget {
			Q_OBJECT

		public:
			EnvironmentWidgetImpl(QWidget* parent);

			void RefreshPanel() override;

		private slots:
			void OnAmbientLightColorChanged(glm::vec3 color);
			void OnAmbientLightIntensityChanged(double intensity);
			void OnDirectionalLightPositionChanged(glm::vec3 position);
			void OnDirectionalLightColorChanged(glm::vec3 color);
			void OnDirectionalLightIntensityChanged(double intensity);

		private:
			void InitConnections();

		private:
			std::shared_ptr<pawn::engine::Environment> m_Environment;

			QGroupBox* m_AmbientLightGroupBox;
			Double3Widget* m_AmbientLightColor;
			DoubleLabelWidget* m_AmbientLightIntensity;

			QGroupBox* m_DirectionalLightGroupBox;
			Double3Widget* m_DirectionalLightPosition;
			Double3Widget* m_DirectionalLightColor;
			DoubleLabelWidget* m_DirectionalLightIntensity;
	};

}
