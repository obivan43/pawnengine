#pragma once

namespace pawn {
	
	class CameraInputHandler {
		
		public:
			void MoveCamera(Camera& camera, Clock clock);

		private:
			void MoveFront(Camera& camera, Clock clock) const;
			void MoveBack(Camera& camera, Clock clock) const;
			void MoveLeft(Camera& camera, Clock clock) const;
			void MoveRight(Camera& camera, Clock clock) const;

			void MouseMove(Camera& camera, Clock clock, glm::vec2 position);

		private:
			const float m_MovementSpeed = 2.5f;
			const float m_MouseSensitivity = 0.1f;
			glm::vec2 previousPosition = { 0.0f, 0.0f };

			float m_Yaw = 90.0f;
			float m_Pitch = 0.0f;
	};
	
}
