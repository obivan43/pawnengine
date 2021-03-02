#pragma once

namespace pawn {
	
	class Scene {
		
		public:
			Scene();
			Scene(const Scene& other) = delete;
			Scene(Scene&& other) noexcept = default;

			Scene& operator=(const Scene& other) = delete;
			Scene& operator=(Scene&& other) noexcept = delete;
	};
	
}
