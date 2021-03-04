#include "pch.h"
#include "CameraInputHandler.h"
#include "Application.h"

#include "ext/matrix_transform.hpp"

namespace pawn {

	void CameraInputHandler::MoveCamera(Camera& camera, Clock clock) {
		static pawn::Window& window = Application::Instance().GetWindow();
		static KeyboardInputManager& keyboard = window.GetKeyBoardInputManager();
		static MouseInputManager& mouse = window.GetMouseInputManager();

		bool IsRotated = false;

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

		if (keyboard.IsPressed(VK_UP)) {
			RotateUp(camera, clock);
			IsRotated = true;
		}

		if (keyboard.IsPressed(VK_DOWN)) {
			RotateDown(camera, clock);
			IsRotated = true;
		}

		if (keyboard.IsPressed(VK_LEFT)) {
			RotateLeft(camera, clock);
			IsRotated = true;
		}

		if (keyboard.IsPressed(VK_RIGHT)) {
			RotateRight(camera, clock);
			IsRotated = true;
		}

		if (IsRotated) {
			RecalculateViewDirection(camera);
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

	void CameraInputHandler::RotateUp(Camera& camera, Clock clock) {
		m_Pitch += m_RotationSpeed * clock.DeltaTime();
	}

	void CameraInputHandler::RotateDown(Camera& camera, Clock clock) {
		m_Pitch -= m_RotationSpeed * clock.DeltaTime();
	}

	void CameraInputHandler::RotateLeft(Camera& camera, Clock clock) {
		m_Yaw += m_RotationSpeed * clock.DeltaTime() ;
	}

	void CameraInputHandler::RotateRight(Camera& camera, Clock clock) {
		m_Yaw -= m_RotationSpeed * clock.DeltaTime();
	}

	void CameraInputHandler::RecalculateViewDirection(Camera& camera) {
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
