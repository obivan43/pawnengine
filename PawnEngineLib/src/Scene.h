#pragma once

namespace pawn {

	class Entity;
	
	class Scene {

		friend Entity;
		
		public:
			Scene() = default;
			Scene(const Scene& other) = delete;
			Scene(Scene&& other) noexcept = default;

			Scene& operator=(const Scene& other) = delete;
			Scene& operator=(Scene&& other) noexcept = delete;

			Entity CreateEntity(const std::string& name = std::string());
	
		private:
			entt::registry m_EnttRegistry;
	};
	
}
