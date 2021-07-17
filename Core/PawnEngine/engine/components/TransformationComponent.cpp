#include "TransformationComponent.h"

#include "gtc/matrix_transform.hpp"

namespace pawn {

	namespace engine {

		TransformationComponent::TransformationComponent(const glm::vec3& position) : Position(position) {}

	}
}
