#include "EnvironmentWidgetImpl.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

namespace editor::impl {

	EnvironmentWidgetImpl::EnvironmentWidgetImpl(QWidget* parent)
		: EnvironmentWidget(parent)
		, m_GroupBox(nullptr)
		, m_LightPosition(nullptr)
		, m_LightColor(nullptr)
		, m_AmbientLightIntensity(nullptr)
		, m_DiffuseLightIntensity(nullptr) {

		m_LightPosition = new Double3Widget("Light Position", glm::vec3(1.0), this);

		m_LightColor = new Double3Widget("Light Color", glm::vec3(1.0), this);
		m_LightColor->SetMinMax(0.0, 1.0);

		m_AmbientLightIntensity = new DoubleLabelWidget("Ambient Light Intensity", 1.0);
		m_AmbientLightIntensity->SetMinMax(0.0, 1.0);

		m_DiffuseLightIntensity = new DoubleLabelWidget("Diffuse Light Intensity", 1.0);
		m_DiffuseLightIntensity->SetMinMax(0.0, 1.0);

		QFormLayout* lightLayout = new QFormLayout();
		m_GroupBox = new QGroupBox("Light");
	
		lightLayout->addRow(m_LightPosition);
		lightLayout->addRow(m_LightColor);
		lightLayout->addRow(m_AmbientLightIntensity);
		lightLayout->addRow(m_DiffuseLightIntensity);

		m_GroupBox->setLayout(lightLayout);

		QVBoxLayout* layout = new QVBoxLayout(this);

		layout->addWidget(m_GroupBox);

		setLayout(layout);

		InitConnections();
	}

	void EnvironmentWidgetImpl::InitConnections() {
		connect(m_LightColor, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnLightColorChanged(glm::vec3)));
		connect(m_AmbientLightIntensity, SIGNAL(ValueChanged(double)), this, SLOT(OnAmbientLightIntensityChanged(double)));
		connect(m_LightPosition, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnLightPositionChanged(glm::vec3)));
		connect(m_DiffuseLightIntensity, SIGNAL(ValueChanged(double)), this, SLOT(OnDiffuseLightIntensityChanged(double)));
	}

	void EnvironmentWidgetImpl::OnLightPositionChanged(glm::vec3 position) {
		if (m_Environment.get()) {
			m_Environment->GetLight().SetLightPosition(position);
		}
	}

	void EnvironmentWidgetImpl::OnLightColorChanged(glm::vec3 color) {
		if (m_Environment.get()) {
			m_Environment->GetLight().SetLightColor(color);
		}
	}

	void EnvironmentWidgetImpl::OnAmbientLightIntensityChanged(double intensity) {
		if (m_Environment.get()) {
			m_Environment->GetLight().SetAmbientIntensity(intensity);
		}
	}

	void EnvironmentWidgetImpl::OnDiffuseLightIntensityChanged(double intensity) {
		if (m_Environment.get()) {
			m_Environment->GetLight().SetDiffuseIntensity(intensity);
		}
	}

	void EnvironmentWidgetImpl::RefreshPanel() {
		m_Environment = m_EngineManager->GetEngine()->GetScene()->GetEnvironment();

		const pawn::engine::Light& light = m_Environment->GetLight();

		m_LightPosition->SetValue(light.GetLightPosition());
		m_LightColor->SetValue(light.GetLightColor());
		m_AmbientLightIntensity->SetValue(static_cast<double>(light.GetAmbientIntensity()));
		m_DiffuseLightIntensity->SetValue(static_cast<double>(light.GetDiffuseIntensity()));
	}

}
