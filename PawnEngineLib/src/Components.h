#pragma once

namespace pawn {
	class Mesh;
}

struct TransformComponent {

	TransformComponent() = default;
	TransformComponent(const glm::mat4& transform) : m_Transform(transform) {};
	TransformComponent(const TransformComponent& other) = default;
	TransformComponent(TransformComponent&& other) noexcept = default;

	TransformComponent& operator=(const TransformComponent& other) = default;
	TransformComponent& operator=(TransformComponent&& other) noexcept = default;

	operator glm::mat4& () { return m_Transform; }
	operator const glm::mat4&() const { return m_Transform; }
	
	glm::mat4 m_Transform = glm::mat4(1.0f);
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