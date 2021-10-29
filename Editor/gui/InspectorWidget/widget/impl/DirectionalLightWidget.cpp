#include "DirectionalLightWidget.h"

#include <QFormLayout>

namespace editor::impl {

	DirectionalLightWidget::DirectionalLightWidget(QWidget* parent)
		: QWidget(parent), m_DirectionalLight(nullptr) {
		QFormLayout* layout = new QFormLayout(this);

		m_Ambient = new Double3Widget("Ambient", glm::vec3(1.0f));
		m_Diffuse = new Double3Widget("Diffuse", glm::vec3(1.0f));
		m_Specular = new Double3Widget("Specular", glm::vec3(1.0f));
		m_Direction = new Double3Widget("Direction", glm::vec3(1.0f));

		m_Ambient->SetMinMax(0.0, 1.0);
		m_Diffuse->SetMinMax(0.0, 1.0);
		m_Specular->SetMinMax(0.0, 1.0);

		m_AmbientIntensity = new DoubleLabelWidget("Ambient intensity", 1.0);
		m_DiffuseIntensity = new DoubleLabelWidget("Diffuse intensity", 1.0);
		m_SpecularIntensity = new DoubleLabelWidget("Specular intensity", 1.0);

		m_AmbientIntensity->SetMinMax(0.0, 1.0);
		m_DiffuseIntensity->SetMinMax(0.0, 1.0);
		m_SpecularIntensity->SetMinMax(0.0, 1.0);

		layout->addRow(m_Ambient);
		layout->addRow(m_Diffuse);
		layout->addRow(m_Specular);
		layout->addRow(m_Direction);
		layout->addRow(m_AmbientIntensity);
		layout->addRow(m_DiffuseIntensity);
		layout->addRow(m_SpecularIntensity);

		setLayout(layout);

		InitConnections();
	}

	void DirectionalLightWidget::OnAmbientChanged(glm::vec3 ambient) {
		if (m_DirectionalLight) {
			m_DirectionalLight->Light.SetAmbient(ambient);
		}
	}

	void DirectionalLightWidget::OnDeffuseChanged(glm::vec3 diffuse) {
		if (m_DirectionalLight) {
			m_DirectionalLight->Light.SetDiffuse(diffuse);
		}
	}

	void DirectionalLightWidget::OnSpecularChanged(glm::vec3 specular) {
		if (m_DirectionalLight) {
			m_DirectionalLight->Light.SetSpecular(specular);
		}
	}

	void DirectionalLightWidget::OnDirectionChanged(glm::vec3 direction) {
		if (m_DirectionalLight) {
			m_DirectionalLight->Light.SetDirection(direction);
		}
	}

	void DirectionalLightWidget::OnAmbientIntensityChanged(double intensity) {
		if (m_DirectionalLight) {
			m_DirectionalLight->Light.SetAmbientIntensity(static_cast<float>(intensity));
		}
	}

	void DirectionalLightWidget::OnDeffuseIntensityChanged(double intensity) {
		if (m_DirectionalLight) {
			m_DirectionalLight->Light.SetDiffuseIntensity(static_cast<float>(intensity));
		}
	}

	void DirectionalLightWidget::OnSpecularIntensityChanged(double intensity) {
		if (m_DirectionalLight) {
			m_DirectionalLight->Light.SetSpecularIntensity(static_cast<float>(intensity));
		}
	}

	void DirectionalLightWidget::InitConnections() {
		connect(m_Ambient, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnAmbientChanged(glm::vec3)));
		connect(m_Diffuse, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnDeffuseChanged(glm::vec3)));
		connect(m_Specular, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnSpecularChanged(glm::vec3)));
		connect(m_Direction, SIGNAL(ValueChanged(glm::vec3)), this, SLOT(OnDirectionChanged(glm::vec3)));
		connect(m_AmbientIntensity, SIGNAL(ValueChanged(double)), this, SLOT(OnAmbientIntensityChanged(double)));
		connect(m_DiffuseIntensity, SIGNAL(ValueChanged(double)), this, SLOT(OnDeffuseIntensityChanged(double)));
		connect(m_SpecularIntensity, SIGNAL(ValueChanged(double)), this, SLOT(OnSpecularIntensityChanged(double)));
	}

	void DirectionalLightWidget::SetDirectionalLight(pawn::engine::DirectionalLightComponent* directionalLight) {
		m_DirectionalLight = directionalLight;

		m_Ambient->SetValue(m_DirectionalLight->Light.GetAmbient());
		m_Diffuse->SetValue(m_DirectionalLight->Light.GetDiffuse());
		m_Specular->SetValue(m_DirectionalLight->Light.GetSpecular());
		m_Direction->SetValue(m_DirectionalLight->Light.GetDirection());

		m_AmbientIntensity->SetValue(m_DirectionalLight->Light.GetAmbientIntensity());
		m_DiffuseIntensity->SetValue(m_DirectionalLight->Light.GetDiffuseIntensity());
		m_SpecularIntensity->SetValue(m_DirectionalLight->Light.GetSpecularIntensity());
	}

}
