#pragma once

#include "PawnUtils/src/entt.h"
#include "PawnUtils/src/Clock.h"

#include <string>

namespace pawn {

	class Entity;
	class Renderer;

	class Scene {

		friend Entity;
		
		public:
			Scene() = default;
			Scene(const Scene& other) = delete;
			Scene(Scene&& other) noexcept = default;

			Scene& operator=(const Scene& other) = delete;
			Scene& operator=(Scene&& other) noexcept = delete;

			Entity CreateEntity(const std::string& name = std::string());
			void DeleteEntity(entt::entity entity);

			void OnUpdate(Clock& clock, std::shared_ptr<pawn::Renderer>& renderer);

			entt::registry& GetRegistry() { return m_EnttRegistry; }

		private:
			entt::registry m_EnttRegistry;
	};
	
}
