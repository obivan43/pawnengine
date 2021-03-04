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

			void RotateUp(Camera& camera, Clock clock);
			void RotateDown(Camera& camera, Clock clock);
			void RotateLeft(Camera& camera, Clock clock);
			void RotateRight(Camera& camera, Clock clock);

			void RecalculateViewDirection(Camera& camera);

		private:
			const float m_MovementSpeed = 2.5f;
			const float m_RotationSpeed = 50.0f;
			float m_Yaw = 90.0f;
			float m_Pitch = 0.0f;
	};
	
}
