#include "pch.h"
#include "Camera.h"

namespace pawn {


	Camera::Camera(const glm::vec3& position, float fov, float aspectRatio, float zNear, float zFar)
		: m_Pitch(0.0f), m_Yaw(0.0f) {
		m_Position = position;
		m_Projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
	}
	
	void Camera::RecalculateView() {
		m_View = glm::lookAt(
			m_Position,
			glm::vec3(
				m_Position.x - glm::sin(m_Yaw / 180.0f * 3.14f),
				m_Position.y + glm::tan(m_Pitch / 180.0f * 3.14f),
				m_Position.z - glm::cos(m_Yaw / 180.0f * 3.14f)
			),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}

	void Camera::SetPosition(const glm::vec3& position) { m_Position = position; }
	void Camera::SetPitch(float pitch) { m_Pitch = pitch; }
	void Camera::SetYaw(float yaw) { m_Yaw = yaw; }
}