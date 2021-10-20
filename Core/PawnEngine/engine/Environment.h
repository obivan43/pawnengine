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

			const glm::vec3& GetAmbientLightColor() const { return m_AmbientLightColor; }
			float GetAmbientLightIntensity() const { return m_AmbientLightIntensity; }

			void SetAmbientLightColor(const glm::vec3& color) { m_AmbientLightColor = color; }
			void SetAmbientLightIntensity(float intensity) { m_AmbientLightIntensity = intensity; }

		private:
			glm::vec3 m_AmbientLightColor;
			float m_AmbientLightIntensity;
	};

}
