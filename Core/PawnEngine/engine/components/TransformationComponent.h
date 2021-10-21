#pragma once

#include "glm.hpp"

#include "PawnMath/math/Functions.h"

namespace pawn::engine {

		struct TransformationComponent {

			TransformationComponent();
			TransformationComponent(const glm::vec3& position);

			TransformationComponent(const TransformationComponent& other) = default;
			TransformationComponent(TransformationComponent&& other) noexcept = default;

			TransformationComponent& operator=(const TransformationComponent& other) = default;
			TransformationComponent& operator=(TransformationComponent&& other) noexcept = default;

			glm::mat4 GetTransformation() const noexcept;
			glm::vec3 GetFrontUpCross() const noexcept;
			glm::vec3 GetFront() const noexcept;

			glm::vec3 Position;
			glm::vec3 Rotation;
			glm::vec3 Scale;

		};

}
