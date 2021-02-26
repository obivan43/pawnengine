#pragma once

namespace pawn {

	struct ViewProjection {
		glm::mat4 projection;
		glm::mat4 view;
	};
	
	class Camera {

		public:
			Camera(
				const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
				float fov = 65.0f,
				float aspectRatio = 4.0f / 3.0f,
				float zNear = 0.001f,
				float zFar = 1000.0f
			);

			Camera(const Camera& other) = default;
			Camera(Camera&& other) noexcept = default;

			Camera& operator=(const Camera& other) = default;
			Camera& operator=(Camera&& other) noexcept = default;

			void RecalculateView();

			const glm::mat4& GetProjection() const { return m_Projection; }
			const glm::mat4& GetView() const { return m_View; }

			void SetPosition(const glm::vec3& position);
			void SetPitch(float pitch);
			void SetYaw(float yaw);

			const glm::vec3& GetPosition() const { return m_Position; }
			float GetPitch() const { return m_Pitch; }
			float GetYaw() const { return m_Yaw; }

		private:
			glm::mat4 m_Projection;
			glm::mat4 m_View;

			glm::vec3 m_Position;
			float m_Pitch;
			float m_Yaw;
	};
	
}
