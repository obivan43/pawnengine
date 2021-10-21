#pragma once

#include "Editor/gui/EnvironmentWidget/widget/EnvironmentWidget.h"
#include "Editor/gui/InspectorWidget/widget/impl/Double3Widget.h"

#include <QLabel>
#include <QDoubleSpinBox>

namespace editor::impl {

	class EnvironmentWidgetImpl : public EnvironmentWidget {
			Q_OBJECT

		public:
			EnvironmentWidgetImpl(QWidget* parent);

			void RefreshPanel() override;

		private slots:
			void OnAmbientLightColorChanged(glm::vec3 color);
			void OnAmbientLightIntensityChanged(double intensity);

		private:
			void InitConnections();

		private:
			std::shared_ptr<pawn::engine::Environment> m_Environment;
			Double3Widget* m_AmbientLightColor;
			QLabel* m_AmbientLightIntensityLabel;
			QDoubleSpinBox* m_AmbientLightIntensitySpinBox;
	};

}
