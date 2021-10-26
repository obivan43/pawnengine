#pragma once

#include "Editor/gui/CommonWidgets/widgets/Double3Widget.h"
#include "Editor/gui/CommonWidgets/widgets/DoubleLabelWidget.h"
#include "Editor/gui/EnvironmentWidget/widget/EnvironmentWidget.h"


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
			void OnLightPositionChanged(glm::vec3 position);
			void OnLightColorChanged(glm::vec3 color);
			void OnAmbientLightIntensityChanged(double intensity);
			void OnDiffuseLightIntensityChanged(double intensity);

		private:
			void InitConnections();

		private:
			std::shared_ptr<pawn::engine::Environment> m_Environment;

			QGroupBox* m_GroupBox;
			Double3Widget* m_LightPosition;
			Double3Widget* m_LightColor;
			DoubleLabelWidget* m_AmbientLightIntensity;
			DoubleLabelWidget* m_DiffuseLightIntensity;
	};

}
