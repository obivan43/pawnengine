#pragma once

#include "glm.hpp"

namespace pawn {

	namespace math {

		enum CameraType {
			Perspective,
			Orthographic
		};

		class Camera {

			public:
				Camera();
				Camera(const glm::mat4& projection);
				Camera(const Camera& other) = default;
				Camera(Camera && other) noexcept = default;

				Camera& operator=(const Camera & other) = default;
				Camera& operator=(Camera && other) noexcept = default;

				~Camera();

				CameraType GetType() const { return m_Type; }
				const glm::mat4& GetProjection() const { return m_Projection; }

				void SetOrthographic(
					float left = -16.0f,
					float right = 16.0f,
					float bottom = -9.0f,
					float top = 9.0f,
					float zNear = 0.0f,
					float zFar = 100.0f
				);

				void SetPerspective(
					float fov = 45.0f,
					float aspectRatio = 16.0f / 9.0f,
					float zNear = 0.001f,
					float zFar = 1000.0f
				);

			private:
				glm::mat4 m_Projection;
				CameraType m_Type;
		};

	}

}
