#pragma once

#include "glm.hpp"

namespace pawn {

	struct TransformationComponent {

		TransformationComponent() = default;
		TransformationComponent(const glm::mat4& transformation);
		TransformationComponent(const TransformationComponent& other) = default;
		TransformationComponent(TransformationComponent&& other) noexcept = default;

		TransformationComponent& operator=(const TransformationComponent& other) = default;
		TransformationComponent& operator=(TransformationComponent&& other) noexcept = default;

		operator glm::mat4& () { return Transformation; }
		operator const glm::mat4& () const { return Transformation; }

		void Translate(const glm::vec3& position);

		glm::mat4 Transformation = glm::mat4(1.0f);
	};

}