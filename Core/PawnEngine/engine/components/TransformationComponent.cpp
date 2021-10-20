#include "TransformationComponent.h"

#include "gtc/matrix_transform.hpp"

namespace pawn::engine {

	TransformationComponent::TransformationComponent(const glm::vec3& position) : Position(position) {}

}
