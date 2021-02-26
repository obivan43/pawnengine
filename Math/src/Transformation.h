#pragma once

#include "glm.hpp"

namespace pawn {
	
	class Transformation {

		public:

			Transformation(
				const glm::vec3& position = glm::vec3(),
				const glm::vec3& rotation = glm::vec3(),
				const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)
			);

			Transformation(const Transformation& other) = default;
			Transformation(Transformation&& other) noexcept = default;

			Transformation& operator=(const Transformation& other) = default;
			Transformation& operator=(Transformation&& other) noexcept = default;

			const glm::vec3& GetPosition() const { return m_Position; }
			const glm::vec3& GetRotation() const { return m_Rotation; }
			const glm::vec3& GetScale() const { return m_Scale; }

			void SetPosition(const glm::vec3& position);
			void SetRotation(const glm::vec3& rotation);
			void SetScale(const glm::vec3& scale);

			glm::mat4 GetModelMatrix();

		private:
			glm::vec3 m_Position;
			glm::vec3 m_Rotation;
			glm::vec3 m_Scale;
	};
	
}
