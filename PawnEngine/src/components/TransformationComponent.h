#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace pawn {

	struct TransformationComponent {

		TransformationComponent() = default;
		TransformationComponent(const glm::vec3& position);
		TransformationComponent(const TransformationComponent& other) = default;
		TransformationComponent(TransformationComponent&& other) noexcept = default;

		TransformationComponent& operator=(const TransformationComponent& other) = default;
		TransformationComponent& operator=(TransformationComponent&& other) noexcept = default;

		glm::mat4 GetTransformation() {
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 })
				* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 })
				* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });
			return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}

		glm::vec3 Position { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale { 1.0f, 1.0f, 1.0f };
	};

}
