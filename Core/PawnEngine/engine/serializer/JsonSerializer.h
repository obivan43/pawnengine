#pragma once

#include "PawnUtils/utils/json/json.hpp"
#include "PawnUtils/utils/entt/entt.h"

#include "PawnEngine/engine/GameScene.h"
#include "PawnEngine/engine/MeshManager.h"
#include "PawnEngine/engine/TextureManager.h"

namespace pawn::engine {

	class JsonSerializer {

		public:
			JsonSerializer(std::shared_ptr<GameScene>& scene);
			JsonSerializer(const JsonSerializer& other) = delete;
			JsonSerializer(JsonSerializer&& other) noexcept = delete;

			JsonSerializer& operator=(const JsonSerializer& other) = delete;
			JsonSerializer& operator=(JsonSerializer&& other) noexcept = delete;

			nlohmann::json JsonEntities();
			nlohmann::json JsonEntityIds();
			nlohmann::json JsonEntityById(entt::entity id);

			void ParseJsonEntities(const nlohmann::json& j, std::shared_ptr<MeshManager>& meshManager, std::shared_ptr<TextureManager>& textureManager);

		private:
			std::shared_ptr<GameScene> m_Scene;

	};

}
