#include "pch.h"
#include "TransformationComponent.h"

#include "gtc/matrix_transform.hpp"

namespace pawn {

	TransformationComponent::TransformationComponent(const glm::mat4& transformation) : Transformation(transformation) {}

	void TransformationComponent::Translate(const glm::vec3& position) {
		Transformation = glm::translate(Transformation, position);
	}

}
