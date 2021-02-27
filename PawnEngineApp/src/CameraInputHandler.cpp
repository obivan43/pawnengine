#include "pch.h"
#include "CameraInputHandler.h"

#include "Application.h"

namespace pawn {

	void CameraInputHandler::MoveCamera(Camera& camera, Clock clock) const {
		static pawn::Window& window = Application::Instance().GetWindow();
		static KeyboardInputManager& keyboard = window.GetKeyBoardInputManager();

		if (keyboard.IsPressed('W')) {
			MoveFront(camera, clock);
		}

		if (keyboard.IsPressed('S')) {
			MoveBack(camera, clock);
		}

		if (keyboard.IsPressed('A')) {
			MoveLeft(camera, clock);
		}

		if (keyboard.IsPressed('D')) {
			MoveRight(camera, clock);
		}
	}

	void CameraInputHandler::MoveFront(Camera& camera, Clock clock) const {
		camera.m_Position += (m_MovementSpeed * clock.DeltaTime()) * camera.m_ViewDirection;
	}
	
	void CameraInputHandler::MoveBack(Camera& camera, Clock clock) const {
		camera.m_Position += (-m_MovementSpeed * clock.DeltaTime()) * camera.m_ViewDirection;
	}
	
	void CameraInputHandler::MoveLeft(Camera& camera, Clock clock) const {
		const glm::vec3 strafeDirection = glm::cross(camera.m_ViewDirection, camera.m_CameraUP);
		camera.m_Position += (-m_MovementSpeed * clock.DeltaTime()) * strafeDirection;
	}
	
	void CameraInputHandler::MoveRight(Camera& camera, Clock clock) const {
		const glm::vec3 strafeDirection = glm::cross(camera.m_ViewDirection, camera.m_CameraUP);
		camera.m_Position += (m_MovementSpeed * clock.DeltaTime()) * strafeDirection;
	}
	
}
