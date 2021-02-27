#pragma once

namespace pawn {
	
	class CameraInputHandler {
		
		public:
			void MoveCamera(Camera& camera, Clock clock) const;

		private:
			void MoveFront(Camera& camera, Clock clock) const;
			void MoveBack(Camera& camera, Clock clock) const;
			void MoveLeft(Camera& camera, Clock clock) const;
			void MoveRight(Camera& camera, Clock clock) const;

		private:
			const float m_MovementSpeed = 2.5f;
	};
	
}
