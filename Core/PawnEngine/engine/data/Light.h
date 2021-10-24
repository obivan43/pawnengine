#pragma once

#include "glm.hpp"

namespace pawn::engine {

	class Light {

		public:
			Light();
			Light(const Light& other) = default;
			Light(Light&& other) noexcept = default;

			Light& operator=(const Light& other) = default;
			Light& operator=(Light&& other) noexcept = default;

			inline const glm::vec3& GetLightPosition() const noexcept { return m_LightPosition; }
			inline const glm::vec3& GetLightColor() const noexcept { return m_LightColor; }

			inline float GetAmbientIntensity() const noexcept { return m_AmbientIntensity; }
			inline float GetDiffuseIntensity() const noexcept { return m_DiffuseIntensity; }

			inline void SetLightPosition(const glm::vec3& position) noexcept { m_LightPosition = position; }
			inline void SetLightColor(const glm::vec3& color) noexcept { m_LightColor = color; }

			inline void SetAmbientIntensity(float intensity) noexcept { m_AmbientIntensity = intensity; }
			inline void SetDiffuseIntensity(float intensity) noexcept { m_DiffuseIntensity = intensity; }

		private:
			glm::vec3 m_LightPosition;
			glm::vec3 m_LightColor;

			float m_AmbientIntensity;
			float m_DiffuseIntensity;
	};

}
