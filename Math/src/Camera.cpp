#include "pch.h"
#include "Camera.h"

namespace pawn {

	Camera::Camera(const glm::mat4& projection) : m_Projection(projection) {}

	void Camera::SetOrthographic(
		float left,
		float right,
		float bottom,
		float top,
		float near,
		float far
	) {
		m_Projection = glm::ortho(left, right, bottom, top, near, far);
	}

	void Camera::SetPerspective(
		float fov,
		float aspectRatio,
		float zNear,
		float zFar
	) {
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
	}

}
