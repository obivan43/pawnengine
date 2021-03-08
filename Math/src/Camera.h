#pragma once

namespace pawn {

	class Camera {

		public:
			Camera() = default;
			Camera(const glm::mat4& projection);
			Camera(const Camera& other) = default;
			Camera(Camera&& other) noexcept = default;

			Camera& operator=(const Camera& other) = default;
			Camera& operator=(Camera&& other) noexcept = default;

			const glm::mat4& GetProjection() const { return m_Projection; }

			void SetOrthographic(
				float left = -16.0f,
				float right = 16.0f,
				float bottom = -9.0f,
				float top = 9.0f,
				float near = 0.0f,
				float far = 100.0f
			);

			void SetPerspective(
				float fov = 65.0f,
				float aspectRatio = 4.0f / 3.0f,
				float zNear = 0.001f,
				float zFar = 1000.0f
			);

		private:
			glm::mat4 m_Projection;
	};

}
