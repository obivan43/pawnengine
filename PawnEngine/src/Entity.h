#pragma once

#include "Scene.h"

#include <utility>

namespace pawn {
	
	class Entity {
		
		public:
			Entity();
			Entity(entt::entity id, Scene* scene);
			Entity(const Entity& other) = default;
			Entity(Entity&& other) noexcept = default;

			Entity& operator=(const Entity& other) = default;
			Entity& operator=(Entity&& other) noexcept = default;

			bool IsNull() { return m_EntityID == entt::null; }

			template<typename Component>
			bool HasComponent() {
				return m_Scene->m_EnttRegistry.has<Component>(m_EntityID);
			}

			template<typename Component>
			const Component& GetComponent() const {
				return m_Scene->m_EnttRegistry.get<Component>(m_EntityID);
			}
		
			template<typename Component>
			Component& GetComponent() {
				return m_Scene->m_EnttRegistry.get<Component>(m_EntityID);
			}
		
			template<typename Component, typename... Args>
			Component& AddComponent(Args&&... args) {
				return m_Scene->m_EnttRegistry.emplace<Component>(m_EntityID, std::forward<Args>(args)...);
			}
			
			operator entt::entity() const { return m_EntityID; }

			entt::entity GetEntity() const { return m_EntityID; }
			Scene* GetScene() const { return m_Scene; }

		private:
			entt::entity m_EntityID;
			Scene* m_Scene;
	};
	
}
