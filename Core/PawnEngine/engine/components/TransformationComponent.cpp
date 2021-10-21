#include "TransformationComponent.h"

#include "gtc/matrix_transform.hpp"

namespace pawn::engine {

	TransformationComponent::TransformationComponent()
		: Position(0.0f, 0.0, 0.0f)
		, Rotation(0.0f, 0.0, 0.0f)
		, Scale(1.0f, 1.0f, 1.0f) {}

	TransformationComponent::TransformationComponent(const glm::vec3& position) : TransformationComponent() {
		Position = position;
	}

	glm::mat4 TransformationComponent::GetTransformation() const noexcept {
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), { 1, 0, 0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), { 0, 1, 0 })
			* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), { 0, 0, 1 });
		return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
	}

	glm::vec3 TransformationComponent::GetFrontUpCross() const noexcept {
		glm::vec3 front = GetFront();
		return glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	glm::vec3 TransformationComponent::GetFront() const noexcept {
		glm::vec3 front;

		front.x = sin(glm::radians(-Rotation.y)) * cos(glm::radians(Rotation.x));
		front.y = sin(glm::radians(Rotation.x));
		front.z = cos(glm::radians(-Rotation.y)) * cos(glm::radians(Rotation.x));

		return glm::normalize(front);
	}

}
