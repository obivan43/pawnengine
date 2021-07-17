#pragma once

#include <string>

namespace pawn {

	namespace engine {

		struct TagComponent {

			TagComponent() = default;
			TagComponent(const std::string& tag);
			TagComponent(const TagComponent& other) = default;
			TagComponent(TagComponent&& other) noexcept = default;

			TagComponent& operator=(const TagComponent& other) = default;
			TagComponent& operator=(TagComponent&& other) noexcept = default;

			operator std::string& () { return Tag; }
			operator const std::string& () const { return Tag; }

			std::string Tag;
		};

	}

}

