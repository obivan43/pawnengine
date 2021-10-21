#pragma once

#include "glm.hpp"

#include "gtc/matrix_transform.hpp"

namespace pawn::math {

	template<typename T> constexpr T clamp(T value, T min, T max) {
		return (value < min) ? min : (value > max) ? max : value;
	}

	glm::mat4 cameraMatrix(const glm::vec3& cameraPosition, float pitch, float yaw);

}
