#include "pch.h"
#include "CameraInputHandler.h"

#include <ext/matrix_transform.hpp>

#include "Application.h"

namespace pawn {

	void CameraInputHandler::MoveCamera(Camera& camera, Clock clock) {
		static pawn::Window& window = Application::Instance().GetWindow();
		static KeyboardInputManager& keyboard = window.GetKeyBoardInputManager();
		static MouseInputManager& mouse = window.GetMouseInputManager();

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

		MouseMove(camera, clock, glm::vec2(mouse.GetX(), mouse.GetY()));
		spdlog::get("console")->info("Mouse X {}, Y {}", mouse.GetX(), mouse.GetY());
		spdlog::get("console")->info("View X {}, Y {}, Z {}", camera.m_ViewDirection.x, camera.m_ViewDirection.y, camera.m_ViewDirection.z);
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

	void CameraInputHandler::MouseMove(Camera& camera, Clock clock, glm::vec2 position) {
		position *= m_MouseSensitivity;

		m_Yaw += position.x;
		m_Pitch += position.y;
		
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;

		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = -sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front = glm::normalize(front);

		camera.m_ViewDirection = front;
	}
	
}
