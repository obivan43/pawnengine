#pragma once

#include "glm.hpp"

namespace pawn::engine {

	enum class LightType {
		DirectionalLight,
		PointLight,
		SpotLight
	};

	class BaseLight {

		protected:
			BaseLight() = default;
			BaseLight(const BaseLight& other) = default;
			BaseLight(BaseLight && other) noexcept = default;

			BaseLight& operator=(const BaseLight & other) = default;
			BaseLight& operator=(BaseLight && other) noexcept = default;

		public:
			inline const glm::vec4& GetAmbient() const noexcept { return m_Ambient; }
			inline const glm::vec4& GetDiffuse() const noexcept { return m_Diffuse; }
			inline const glm::vec4& GetSpecular() const noexcept { return m_Specular; }
			inline const LightType GetLightType() const noexcept { return m_LightType; }

			inline void SetAmbient(const glm::vec4& ambient) noexcept { m_Ambient = ambient; }
			inline void SetDiffuse(const glm::vec4& diffuse) noexcept { m_Diffuse = diffuse; }
			inline void SetSpecular(const glm::vec4& specular) noexcept { m_Specular = specular; }

		protected:
			glm::vec4 m_Ambient;
			glm::vec4 m_Diffuse;
			glm::vec4 m_Specular;
			LightType m_LightType;
	};

}
