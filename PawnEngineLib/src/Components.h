#pragma once

#include "glm.hpp"

namespace pawn {
	class Mesh;
	class Camera;
}

struct TransformationComponent {

	TransformationComponent() = default;
	TransformationComponent(const glm::mat4& transformation) : m_Transformation(transformation) {};
	TransformationComponent(const TransformationComponent& other) = default;
	TransformationComponent(TransformationComponent&& other) noexcept = default;

	TransformationComponent& operator=(const TransformationComponent& other) = default;
	TransformationComponent& operator=(TransformationComponent&& other) noexcept = default;

	operator glm::mat4& () { return m_Transformation; }
	operator const glm::mat4&() const { return m_Transformation; }
	
	glm::mat4 m_Transformation = glm::mat4(1.0f);
};

struct NameComponent {

	NameComponent() = default;
	NameComponent(const std::string& name) : m_Name(name) {};
	NameComponent(const NameComponent& other) = default;
	NameComponent(NameComponent&& other) noexcept = default;

	NameComponent& operator=(const NameComponent& other) = default;
	NameComponent& operator=(NameComponent&& other) noexcept = default;

	operator std::string& () { return m_Name; }
	operator const std::string& () const { return m_Name; }

	std::string m_Name;
};

struct MeshComponent {

	MeshComponent() = default;
	MeshComponent(const std::shared_ptr<pawn::Mesh>& mesh) : m_Mesh(mesh) {};
	MeshComponent(const MeshComponent& other) = default;
	MeshComponent(MeshComponent&& other) noexcept = default;

	MeshComponent& operator=(const MeshComponent& other) = default;
	MeshComponent& operator=(MeshComponent&& other) noexcept = default;

	operator std::shared_ptr<pawn::Mesh>& () { return m_Mesh; }
	operator const std::shared_ptr<pawn::Mesh>& () const { return m_Mesh; }

	std::shared_ptr<pawn::Mesh> m_Mesh;
};

struct CameraComponent {

	CameraComponent() = default;
	CameraComponent(const glm::mat4& projection) : m_Camera(projection) {};
	CameraComponent(const CameraComponent& other) = default;
	CameraComponent(CameraComponent&& other) noexcept = default;

	CameraComponent& operator=(const CameraComponent& other) = default;
	CameraComponent& operator=(CameraComponent&& other) noexcept = default;

	operator pawn::Camera& () { return m_Camera; }
	operator const pawn::Camera& () const { return m_Camera; }

	pawn::Camera m_Camera;
	bool m_IsActiveCamera = false;

};