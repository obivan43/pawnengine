#pragma once

#include <string>

namespace pawn {

	struct NameComponent {

		NameComponent() = default;
		NameComponent(const std::string& name);
		NameComponent(const NameComponent& other) = default;
		NameComponent(NameComponent&& other) noexcept = default;

		NameComponent& operator=(const NameComponent& other) = default;
		NameComponent& operator=(NameComponent&& other) noexcept = default;

		operator std::string& () { return m_Name; }
		operator const std::string& () const { return m_Name; }

		std::string m_Name;
	};

}
