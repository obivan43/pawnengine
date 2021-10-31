#pragma once

#include "glm.hpp"

namespace pawn::engine {

	class BaseLight {

		protected:
			BaseLight() = default;
			BaseLight(const BaseLight& other) = default;
			BaseLight(BaseLight && other) noexcept = default;

			BaseLight& operator=(const BaseLight & other) = default;
			BaseLight& operator=(BaseLight && other) noexcept = default;

		public:
			inline const glm::vec3& GetAmbient() const noexcept { return m_Ambient; }
			inline float GetAmbientIntensity() const noexcept { return m_AmbientIntensity; }

			inline const glm::vec3& GetDiffuse() const noexcept { return m_Diffuse; }
			inline float GetDiffuseIntensity() const noexcept { return m_DiffuseIntensity; }

			inline const glm::vec3& GetSpecular() const noexcept { return m_Specular; }
			inline float GetSpecularIntensity() const noexcept { return m_SpecularIntensity; }

			inline void SetAmbient(const glm::vec3& ambient) noexcept { m_Ambient = ambient; }
			inline void SetDiffuse(const glm::vec3& diffuse) noexcept { m_Diffuse = diffuse; }
			inline void SetSpecular(const glm::vec3& specular) noexcept { m_Specular = specular; }

			inline void SetAmbientIntensity(float intensity) noexcept { m_AmbientIntensity = intensity; }
			inline void SetDiffuseIntensity(float intensity) noexcept { m_DiffuseIntensity = intensity; }
			inline void SetSpecularIntensity(float intensity) noexcept { m_SpecularIntensity = intensity; }

		protected:
			glm::vec3 m_Ambient;
			float m_AmbientIntensity;

			glm::vec3 m_Diffuse;
			float m_DiffuseIntensity;

			glm::vec3 m_Specular;
			float m_SpecularIntensity;
	};

}
