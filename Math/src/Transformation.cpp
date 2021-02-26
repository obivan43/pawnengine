#include "pch.h"
#include "Transformation.h"

namespace pawn {

	Transformation::Transformation(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

	void Transformation::SetPosition(const glm::vec3& position) {
		m_Position = position;
	}

	void Transformation::SetRotation(const glm::vec3& rotation) {
		m_Rotation = rotation;
	}

	void Transformation::SetScale(const glm::vec3& scale) {
		m_Scale = scale;
	}

	glm::mat4 Transformation::GetModelMatrix() {
		const glm::mat4 positionMatrix = glm::translate(glm::identity<glm::mat4>(), m_Position);

		const glm::quat quaternionRotationX = glm::angleAxis(glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		const glm::quat quaternionRotationY = glm::angleAxis(glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		const glm::quat quaternionRotationZ = glm::angleAxis(glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		const glm::mat4 scaleMatrix = glm::scale(glm::identity<glm::mat4>(), m_Scale);
		const glm::mat4 rotationMatrix = glm::mat4_cast(quaternionRotationX * quaternionRotationY * quaternionRotationZ);

		return positionMatrix * rotationMatrix * scaleMatrix;
	}
	
}