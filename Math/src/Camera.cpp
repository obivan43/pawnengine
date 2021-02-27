#include "pch.h"
#include "Camera.h"

namespace pawn {


	Camera::Camera(const glm::vec3& position, float fov, float aspectRatio, float zNear, float zFar) {
		m_Position = position;
		m_ViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
		m_CameraUP = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
	}
	
	void Camera::RecalculateView() {
		m_View = glm::lookAt(
			m_Position,
			m_Position + m_ViewDirection,
			m_CameraUP
		);
	}
}