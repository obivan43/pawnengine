#include "pch.h"
#include "Camera.h"

namespace pawn {

	namespace math {

		Camera::Camera() : m_Projection(1.0f) {
			SetPerspective();
		}

		Camera::Camera(const glm::mat4& projection) : m_Projection(projection) {
			SetPerspective();
		}

		Camera::~Camera() {}

		void Camera::SetOrthographic(
			float left,
			float right,
			float bottom,
			float top,
			float zNear,
			float zFar
		) {
			m_Projection = glm::ortho(left, right, bottom, top, zNear, zFar);
			m_Type = CameraType::Orthographic;
		}

		void Camera::SetPerspective(
			float fov,
			float aspectRatio,
			float zNear,
			float zFar
		) {
			m_Projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
			m_Type = CameraType::Perspective;
		}

	}

}
