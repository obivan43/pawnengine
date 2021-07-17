#include "GameEntity.h"
#include "GameScene.h"

namespace pawn {

	namespace engine {

		GameEntity::GameEntity() : m_EntityID(entt::null), m_Scene(nullptr) {}

		GameEntity::GameEntity(entt::entity id, GameScene* scene)
			: m_EntityID(id), m_Scene(scene) {}

	}
	
}
