#pragma once

#include <string>

namespace pawn {

	struct TagComponent {

		TagComponent() = default;
		TagComponent(const std::string& name);
		TagComponent(const TagComponent& other) = default;
		TagComponent(TagComponent&& other) noexcept = default;

		TagComponent& operator=(const TagComponent& other) = default;
		TagComponent& operator=(TagComponent&& other) noexcept = default;

		operator std::string& () { return m_Name; }
		operator const std::string& () const { return m_Name; }

		std::string m_Name;
	};

}
