#pragma once

#include "glm.hpp"

#include "PawnMath/math/Camera.h"

namespace pawn::engine {

	struct CameraComponent {

		CameraComponent();
		CameraComponent(const glm::mat4& projection);

		CameraComponent(const CameraComponent& other) = default;
		CameraComponent(CameraComponent&& other) noexcept = default;

		CameraComponent& operator=(const CameraComponent& other) = default;
		CameraComponent& operator=(CameraComponent&& other) noexcept = default;

		inline operator math::Camera& () noexcept { return Camera; }
		inline operator const math::Camera& () const noexcept { return Camera; }

		math::Camera Camera;
		bool IsActiveCamera;

	};

}
