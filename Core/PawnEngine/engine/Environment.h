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

			inline void SetAmbientLightColor(const glm::vec3& color) noexcept { m_AmbientLightColor = color; }
			inline void SetAmbientLightIntensity(float intensity) noexcept { m_AmbientLightIntensity = intensity; }

		private:
			glm::vec3 m_AmbientLightColor;
			float m_AmbientLightIntensity;
	};

}
