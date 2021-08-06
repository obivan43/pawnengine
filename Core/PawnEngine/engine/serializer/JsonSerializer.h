#pragma once

#include "PawnUtils/utils/json/json.hpp"
#include "PawnUtils/utils/entt/entt.h"

#include "PawnEngine/engine/GameScene.h"

using json = nlohmann::json;

namespace pawn {

	namespace engine {

		class JsonSerializer {

			public:
				JsonSerializer(std::shared_ptr<GameScene>& scene);
				JsonSerializer(const JsonSerializer& other) = delete;
				JsonSerializer(JsonSerializer&& other) noexcept = delete;

				JsonSerializer& operator=(const JsonSerializer& other) = delete;
				JsonSerializer& operator=(JsonSerializer&& other) noexcept = delete;

				json JsonEntityIds();
				json JsonEntityById(entt::entity id);

			private:
				std::shared_ptr<GameScene> m_Scene;

		};


	}

}
