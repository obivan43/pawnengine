#include "EnvironmentWidgetImpl.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace editor::impl {

	EnvironmentWidgetImpl::EnvironmentWidgetImpl(QWidget* parent)
		: EnvironmentWidget(parent)
		, m_AmbientLightIntensityLabel(nullptr)
		, m_AmbientLightIntensitySpinBox(nullptr) {
		glm::vec3 ambientLightColor{ 1.0f, 1.0f, 1.0f };
		float ambientLightIntensity{ 1.0f };

		QVBoxLayout* layout = new QVBoxLayout(this);

		m_AmbientLightColor = new Double3Widget("Ambient Light Color", ambientLightColor, this);
		m_AmbientLightColor->SetMinMax(0.0, 1.0);

		layout->addWidget(m_AmbientLightColor);

		QHBoxLayout* lightIntensityLayout = new QHBoxLayout();

		m_AmbientLightIntensityLabel = new QLabel("Ambient Light Intensity", this);
		m_AmbientLightIntensitySpinBox = new QDoubleSpinBox(this);

		m_AmbientLightIntensitySpinBox->setMinimum(0.0);
		m_AmbientLightIntensitySpinBox->setMaximum(1.0);
		m_AmbientLightIntensitySpinBox->setSingleStep(0.05);
		m_AmbientLightIntensitySpinBox->setValue(static_cast<double>(ambientLightIntensity));

		lightIntensityLayout->addWidget(m_AmbientLightIntensityLabel);
		lightIntensityLayout->addWidget(m_AmbientLightIntensitySpinBox);

		layout->addLayout(lightIntensityLayout);

		setLayout(layout);

		setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

		InitConnections();
	}

	void EnvironmentWidgetImpl::InitConnections() {
		connect(m_AmbientLightColor, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnAmbientLightColorChanged(glm::vec3)));
		connect(m_AmbientLightIntensitySpinBox, SIGNAL(valueChanged(double)), this, SLOT(OnAmbientLightIntensityChanged(double)));
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

	void EnvironmentWidgetImpl::RefreshPanel() {
		m_Environment = m_EngineManager->GetEngine()->GetScene()->GetEnvironment();
		m_AmbientLightIntensitySpinBox->setValue(static_cast<double>(m_Environment->GetAmbientLightIntensity()));
		m_AmbientLightColor->SetValue(m_Environment->GetAmbientLightColor());
	}

}