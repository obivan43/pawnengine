#include "EnvironmentWidgetImpl.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

namespace editor::impl {

	EnvironmentWidgetImpl::EnvironmentWidgetImpl(QWidget* parent)
		: EnvironmentWidget(parent)
		, m_AmbientLightGroupBox(nullptr)
		, m_AmbientLightIntensity(nullptr)
		, m_DirectionalLightGroupBox(nullptr)
		, m_DirectionalLightPosition(nullptr)
		, m_DirectionalLightColor(nullptr)
		, m_DirectionalLightIntensity(nullptr) {

		m_AmbientLightColor = new Double3Widget("Ambient Light Color", glm::vec3(1.0), this);
		m_AmbientLightColor->SetMinMax(0.0, 1.0);

		m_AmbientLightIntensity = new DoubleLabelWidget("Ambient Light Intensity", 1.0);
		m_AmbientLightIntensity->SetMinMax(0.0, 1.0);

		m_DirectionalLightPosition = new Double3Widget("Directional Light Position", glm::vec3(1.0), this);

		m_DirectionalLightColor = new Double3Widget("Directional Light Color", glm::vec3(1.0), this);
		m_DirectionalLightColor->SetMinMax(0.0, 1.0);

		m_DirectionalLightIntensity = new DoubleLabelWidget("Directional Light Intensity", 1.0);
		m_DirectionalLightIntensity->SetMinMax(0.0, 1.0);

		QFormLayout* ambientLayout = new QFormLayout();
		m_AmbientLightGroupBox = new QGroupBox("Ambient Light");
	
		ambientLayout->addRow(m_AmbientLightColor);
		ambientLayout->addRow(m_AmbientLightIntensity);

		m_AmbientLightGroupBox->setLayout(ambientLayout);

		QFormLayout* directionalLayout = new QFormLayout();
		m_DirectionalLightGroupBox = new QGroupBox("Directional Light");

		directionalLayout->addRow(m_DirectionalLightPosition);
		directionalLayout->addRow(m_DirectionalLightColor);
		directionalLayout->addRow(m_DirectionalLightIntensity);

		m_DirectionalLightGroupBox->setLayout(directionalLayout);

		QVBoxLayout* layout = new QVBoxLayout(this);

		layout->addWidget(m_AmbientLightGroupBox);
		layout->addWidget(m_DirectionalLightGroupBox);

		setLayout(layout);

		InitConnections();
	}

	void EnvironmentWidgetImpl::InitConnections() {
		connect(m_AmbientLightColor, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnAmbientLightColorChanged(glm::vec3)));
		connect(m_AmbientLightIntensity, SIGNAL(ValueChanged(double)), this, SLOT(OnAmbientLightIntensityChanged(double)));
		connect(m_DirectionalLightPosition, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnDirectionalLightPositionChanged(glm::vec3)));
		connect(m_DirectionalLightColor, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnDirectionalLightColorChanged(glm::vec3)));
		connect(m_DirectionalLightIntensity, SIGNAL(ValueChanged(double)), this, SLOT(OnDirectionalLightIntensityChanged(double)));
	}

	void EnvironmentWidgetImpl::OnAmbientLightColorChanged(glm::vec3 color) {
		if (m_Environment.get()) {
			m_Environment->SetAmbientLightColor(color);
		}
	}

	void EnvironmentWidgetImpl::OnAmbientLightIntensityChanged(double intensity) {
		if (m_Environment.get()) {
			m_Environment->SetAmbientLightIntensity(intensity);
		}
	}

	void EnvironmentWidgetImpl::OnDirectionalLightPositionChanged(glm::vec3 position) {
		if (m_Environment.get()) {
			m_Environment->SetDirectionalLightPosition(position);
		}
	}

	void EnvironmentWidgetImpl::OnDirectionalLightColorChanged(glm::vec3 color) {
		if (m_Environment.get()) {
			m_Environment->SetDirectionalLightColor(color);
		}
	}

	void EnvironmentWidgetImpl::OnDirectionalLightIntensityChanged(double intensity) {
		if (m_Environment.get()) {
			m_Environment->SetDirectionalLightIntensity(intensity);
		}
	}

	void EnvironmentWidgetImpl::RefreshPanel() {
		m_Environment = m_EngineManager->GetEngine()->GetScene()->GetEnvironment();
		m_AmbientLightColor->SetValue(m_Environment->GetAmbientLightColor());
		m_AmbientLightIntensity->SetValue(static_cast<double>(m_Environment->GetAmbientLightIntensity()));
		m_DirectionalLightPosition->SetValue(m_Environment->GetDirectionalLightPosition());
		m_DirectionalLightColor->SetValue(m_Environment->GetDirectionalLightColor());
		m_DirectionalLightIntensity->SetValue(static_cast<double>(m_Environment->GetDirectionalLightIntensity()));
	}

}
