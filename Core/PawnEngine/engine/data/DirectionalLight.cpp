#include "DirectionalLight.h"

namespace pawn::engine {

	DirectionalLight::DirectionalLight() : m_Direction(0.0f, 0.0f, 0.0f) {
		m_Ambient = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Specular = glm::vec3(1.0f, 1.0f, 1.0f);
		m_AmbientIntensity = 0.2f;
		m_DiffuseIntensity = 1.0f;
		m_SpecularIntensity = 1.0f;
	}

}
