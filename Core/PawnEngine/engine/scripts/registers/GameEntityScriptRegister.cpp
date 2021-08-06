#include "GameEntityScriptRegister.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/components/TransformationComponent.h"


namespace pawn {

	namespace engine {

		void GameEntityScriptRegister::Register(sol::state& lua) {
			lua.new_usertype<pawn::engine::GameEntity>("GameEntity",
				sol::constructors<pawn::engine::GameEntity(), pawn::engine::GameEntity(const GameEntity&), pawn::engine::GameEntity(GameEntity&&)>(),
				"id", sol::property(&pawn::engine::GameEntity::GetEntity),
				"transformation", sol::property(
					[](const pawn::engine::GameEntity& entity) {
						pawn::engine::TransformationComponent transform = entity.GetComponent<pawn::engine::TransformationComponent>();
						return transform;
					},

					[](pawn::engine::GameEntity& entity, pawn::engine::TransformationComponent newTransformation) {
						pawn::engine::TransformationComponent& transform = entity.GetComponent<pawn::engine::TransformationComponent>();
						transform = newTransformation;
					}
				)
			);
		}

	}

}