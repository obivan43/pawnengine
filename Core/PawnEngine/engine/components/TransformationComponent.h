#pragma once

#include "PawnMath/math/Functions.h"

#include "glm.hpp"

namespace pawn::engine {

		struct TransformationComponent {

			TransformationComponent() = default;
			TransformationComponent(const glm::vec3& position);
			TransformationComponent(const TransformationComponent& other) = default;
			TransformationComponent(TransformationComponent&& other) noexcept = default;

			TransformationComponent& operator=(const TransformationComponent& other) = default;
			TransformationComponent& operator=(TransformationComponent&& other) noexcept = default;

			glm::mat4 GetTransformation() {
				glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), { 1, 0, 0 })
					* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), { 0, 1, 0 })
					* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), { 0, 0, 1 });
				return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
			}

			glm::vec3 GetFrontUpCross() {
				glm::vec3 front = GetFront();
				return glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0)));
			}

			glm::vec3 GetFront() {
				glm::vec3 front;

				front.x = sin(glm::radians(-Rotation.y)) * cos(glm::radians(Rotation.x));
				front.y = sin(glm::radians(Rotation.x));
				front.z = cos(glm::radians(-Rotation.y)) * cos(glm::radians(Rotation.x));

				return glm::normalize(front);
			}

			glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
			glm::vec3 Rotation{ 0.0f, 0.0f, 0.0f };
			glm::vec3 Scale{ 1.0f, 1.0f, 1.0f };

		};

}
