#include "DirectionalLight.h"

namespace pawn::engine {

	DirectionalLight::DirectionalLight() : m_Direction(0.0f, 0.0f, 0.0f) {
		m_Ambient = glm::vec4(1.0f, 1.0f, 1.0f, 0.2f);
		m_Diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_LightType = LightType::DirectionalLight;
	}

}
