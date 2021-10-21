#pragma once

#include "Environment.h"
#include "glm.hpp"

#include "PawnMath/math/Camera.h"
#include "PawnUtils/utils/entt/entt.h"
#include "PawnUtils/utils/time/Clock.h"

#include <string>

namespace pawn::engine {

	class GameEntity;
	class Renderer;
	class ScriptEngine;

	class GameScene {

		friend GameEntity;

		public:
			GameScene();
			GameScene(const GameScene& other) = delete;
			GameScene(GameScene&& other) noexcept = default;

			GameScene& operator=(const GameScene& other) = delete;
			GameScene& operator=(GameScene&& other) noexcept = delete;

			GameEntity CreateEntity(const std::string& name = std::string());
			GameEntity CreateEntity(uint32_t hint, const std::string& name = std::string());

			void DeleteEntity(entt::entity entity);
			void Clear();

			void OnCreate(std::shared_ptr<ScriptEngine>& scriptEngine);
			void OnUpdate(utils::Clock& clock, std::shared_ptr<ScriptEngine>& scriptEngine);
			void OnRender(std::shared_ptr<Renderer>& renderer);

			inline entt::registry& GetRegistry() noexcept { return m_EnttRegistry; }
			inline std::shared_ptr<Environment> GetEnvironment() noexcept { return m_Environment; }

		private:
			void FindActiveCamera();

		private:
			entt::registry m_EnttRegistry;

			math::Camera* m_ActiveCamera;
			glm::mat4 m_ActiveCameraView;

			std::shared_ptr<Environment> m_Environment;
	};

}
