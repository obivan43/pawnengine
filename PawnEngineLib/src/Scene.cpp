#include "pch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

namespace pawn {

	Entity Scene::CreateEntity(const std::string& name) {
		static uint32_t namedEntityID = 0;
		const entt::entity entityID = m_EnttRegistry.create();
		
		m_EnttRegistry.emplace<TransformationComponent>(entityID);
		m_EnttRegistry.emplace<NameComponent>(entityID, name == "" ? ("Entity_" + namedEntityID++) : name);
		
		const Entity entity(entityID, this);
		return entity;
	}
	
	void Scene::DeleteEntity(Entity& entity) {
		m_EnttRegistry.destroy(entity);
	}


	void Scene::OnUpdate(Clock& clock) {}

}