#include "pch.h"
#include "Entity.h"
#include "Scene.h"

namespace pawn {

	Entity::Entity() : m_EntityID(entt::null), m_Scene(nullptr) {}
	
	Entity::Entity(entt::entity id, Scene* scene)
	: m_EntityID(id), m_Scene(scene) {}
	
}