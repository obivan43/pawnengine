#pragma once

#include "glm.hpp"
#include "PawnMath/src/Camera.h"

namespace pawn {

	struct CameraComponent {

		CameraComponent() = default;
		CameraComponent(const glm::mat4& projection);
		CameraComponent(const CameraComponent& other) = default;
		CameraComponent(CameraComponent&& other) noexcept = default;

		CameraComponent& operator=(const CameraComponent& other) = default;
		CameraComponent& operator=(CameraComponent&& other) noexcept = default;

		operator pawn::Camera& () { return m_Camera; }
		operator const pawn::Camera& () const { return m_Camera; }

		pawn::Camera m_Camera;
		bool m_IsActiveCamera = false;

	};

}