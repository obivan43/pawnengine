#include "pch.h"
#include "CameraComponent.h"

namespace pawn {

	CameraComponent::CameraComponent(const glm::mat4& projection) : m_Camera(projection) {}

}