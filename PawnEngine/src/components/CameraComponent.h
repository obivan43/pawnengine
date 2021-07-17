#pragma once

#include "glm.hpp"
#include "PawnMath/math/Camera.h"

namespace pawn {

	struct CameraComponent {

		CameraComponent() = default;
		CameraComponent(const glm::mat4& projection);
		CameraComponent(const CameraComponent& other) = default;
		CameraComponent(CameraComponent&& other) noexcept = default;

		CameraComponent& operator=(const CameraComponent& other) = default;
		CameraComponent& operator=(CameraComponent&& other) noexcept = default;

		operator pawn::Camera& () { return Camera; }
		operator const pawn::Camera& () const { return Camera; }

		pawn::Camera Camera;
		bool IsActiveCamera = false;

	};

}