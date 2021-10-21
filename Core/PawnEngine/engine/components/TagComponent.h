#pragma once

#include <string>

namespace pawn::engine {

	struct TagComponent {

		TagComponent() = default;
		TagComponent(const std::string& tag);

		TagComponent(const TagComponent& other) = default;
		TagComponent(TagComponent&& other) noexcept = default;

		TagComponent& operator=(const TagComponent& other) = default;
		TagComponent& operator=(TagComponent&& other) noexcept = default;

		inline operator std::string& () noexcept { return Tag; }
		inline operator const std::string& () const noexcept { return Tag; }

		std::string Tag;
	};

}
