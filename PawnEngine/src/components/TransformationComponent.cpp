#include "pch.h"
#include "TransformationComponent.h"

#include "gtc/matrix_transform.hpp"

namespace pawn {

	TransformationComponent::TransformationComponent(const glm::vec3& position) : Position(position) {}

}
