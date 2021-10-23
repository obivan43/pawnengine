#pragma once

#include "glm.hpp"

namespace pawn::engine {

	class Environment {

		public:
			Environment();
			Environment(const Environment& other) = delete;
			Environment(Environment&& other) noexcept = delete;

			Environment& operator=(const Environment& other) = delete;
			Environment& operator=(Environment&& other) noexcept = delete;

			inline const glm::vec3& GetAmbientLightColor() const noexcept { return m_AmbientLightColor; }
			inline float GetAmbientLightIntensity() const noexcept { return m_AmbientLightIntensity; }

			inline const glm::vec3& GetDirectionalLightPosition() const noexcept { return m_DirectionalLightPosition; }
			inline const glm::vec3& GetDirectionalLightColor() const noexcept { return m_DirectionalLightColor; }
			inline float GetDirectionalLightIntensity() const noexcept { return m_DirectionalLightIntensity; }

			inline void SetAmbientLightColor(const glm::vec3& color) noexcept { m_AmbientLightColor = color; }
			inline void SetAmbientLightIntensity(float intensity) noexcept { m_AmbientLightIntensity = intensity; }

			inline void SetDirectionalLightPosition(const glm::vec3& position) noexcept { m_DirectionalLightPosition = position; }
			inline void SetDirectionalLightColor(const glm::vec3& color) noexcept { m_DirectionalLightColor = color; }
			inline void SetDirectionalLightIntensity(float intensity) noexcept { m_DirectionalLightIntensity = intensity; }

		private:
			glm::vec3 m_AmbientLightColor;
			float m_AmbientLightIntensity;

			glm::vec3 m_DirectionalLightPosition;
			glm::vec3 m_DirectionalLightColor;
			float m_DirectionalLightIntensity;
	};

}
