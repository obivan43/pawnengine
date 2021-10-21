#include "CameraComponent.h"

namespace pawn::engine {

	CameraComponent::CameraComponent() : Camera(glm::mat4(1.0f)), IsActiveCamera(false) {}

	CameraComponent::CameraComponent(const glm::mat4& projection) : Camera(projection), IsActiveCamera(false) {}

}
