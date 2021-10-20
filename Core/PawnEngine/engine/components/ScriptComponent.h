#pragma once

#include <string>

namespace pawn::engine {

	struct ScriptComponent {

		ScriptComponent() = default;
		ScriptComponent(const std::string& fileName);
		ScriptComponent(const ScriptComponent& other) = default;
		ScriptComponent(ScriptComponent&& other) noexcept = default;

		ScriptComponent& operator=(const ScriptComponent& other) = default;
		ScriptComponent& operator=(ScriptComponent&& other) noexcept = default;

		operator std::string& () { return FileName; }
		operator const std::string& () const { return FileName; }

		std::string FileName;
	};

}
