#pragma once

#include "PawnUtils/utils/entt/entt.h"
#include "PawnUtils/utils/time/Clock.h"

#include <string>

namespace pawn {

	class GameEntity;
	class Renderer;

	class GameScene {

		friend GameEntity;
		
		public:
			GameScene() = default;
			GameScene(const GameScene& other) = delete;
			GameScene(GameScene&& other) noexcept = default;

			GameScene& operator=(const GameScene& other) = delete;
			GameScene& operator=(GameScene&& other) noexcept = delete;

			GameEntity CreateEntity(const std::string& name = std::string());
			void DeleteEntity(entt::entity entity);

			void OnUpdate(Clock& clock, std::shared_ptr<pawn::Renderer>& renderer);

			entt::registry& GetRegistry() { return m_EnttRegistry; }

		private:
			entt::registry m_EnttRegistry;
	};
	
}
