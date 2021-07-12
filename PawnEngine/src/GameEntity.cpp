#include "pch.h"
#include "GameEntity.h"
#include "GameScene.h"

namespace pawn {

	GameEntity::GameEntity() : m_EntityID(entt::null), m_Scene(nullptr) {}
	
	GameEntity::GameEntity(entt::entity id, GameScene* scene)
	: m_EntityID(id), m_Scene(scene) {}
	
}