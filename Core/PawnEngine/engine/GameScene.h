#pragma once

#include "PawnUtils/utils/entt/entt.h"
#include "PawnUtils/utils/time/Clock.h"

#include "PawnMath/math/Camera.h"

#include <string>

#include <glm.hpp>

namespace pawn {

	namespace engine {

		class GameEntity;
		class Renderer;
		class ScriptEngine;

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

				void OnCreate(std::shared_ptr<ScriptEngine>& scriptEngine);
				void OnUpdate(utils::Clock& clock, std::shared_ptr<ScriptEngine>& scriptEngine);
				void OnRender(std::shared_ptr<Renderer>& renderer);

				entt::registry& GetRegistry() { return m_EnttRegistry; }

			private:
				void FindActiveCamera();

			private:
				math::Camera* m_ActiveCamera;
				glm::mat4 m_ActiveCameraView;
				entt::registry m_EnttRegistry;
		};

	}
	
}
