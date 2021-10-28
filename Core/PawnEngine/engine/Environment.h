#pragma once

namespace pawn::engine {

	class Environment {

		public:
			Environment();
			Environment(const Environment& other) = delete;
			Environment(Environment&& other) noexcept = delete;

			Environment& operator=(const Environment& other) = delete;
			Environment& operator=(Environment&& other) noexcept = delete;
		
	};

}
