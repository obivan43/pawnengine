#pragma once

#include "BaseLight.h"

namespace pawn::engine {

	class DirectionalLight : public BaseLight {

		public:
			DirectionalLight();
			DirectionalLight(const DirectionalLight& other) = default;
			DirectionalLight(DirectionalLight&& other) noexcept = default;

			DirectionalLight& operator=(const DirectionalLight& other) = default;
			DirectionalLight& operator=(DirectionalLight&& other) noexcept = default;

			inline const glm::vec3& GetDirection() const noexcept { return m_Direction; }
		
			inline void SetDirection(const glm::vec3& direction) noexcept { m_Direction = direction; }

		private:
			glm::vec3 m_Direction;
	};

}
