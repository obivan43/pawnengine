#pragma once

struct TransformComponent {

	TransformComponent() = default;
	TransformComponent(const glm::mat4& transform) : Transform(transform) {};
	TransformComponent(const TransformComponent& other) = default;
	TransformComponent(TransformComponent&& other) noexcept = default;

	TransformComponent& operator=(const TransformComponent& other) = default;
	TransformComponent& operator=(TransformComponent&& other) noexcept = default;

	operator glm::mat4& () { return Transform; }
	operator const glm::mat4&() const { return Transform; }
	
	glm::mat4 Transform = glm::mat4(1.0f);
};

struct NameComponent {

	NameComponent() = default;
	NameComponent(const std::string& name) : Name(name) {};
	NameComponent(const NameComponent& other) = default;
	NameComponent(NameComponent&& other) noexcept = default;

	NameComponent& operator=(const NameComponent& other) = default;
	NameComponent& operator=(NameComponent&& other) noexcept = default;

	operator std::string& () { return Name; }
	operator const std::string& () const { return Name; }

	std::string Name;
};
