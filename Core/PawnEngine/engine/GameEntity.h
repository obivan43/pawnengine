#pragma once

#include "GameScene.h"

#include <utility>

namespace pawn {
	
	namespace engine {

		class GameEntity {

			public:
				GameEntity();
				GameEntity(entt::entity id, GameScene* scene);
				GameEntity(const GameEntity& other) = default;
				GameEntity(GameEntity&& other) noexcept = default;

				GameEntity& operator=(const GameEntity& other) = default;
				GameEntity& operator=(GameEntity&& other) noexcept = default;

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

				bool operator==(const GameEntity& other) {
					return m_EntityID == other.m_EntityID;
				}

				operator entt::entity() const { return m_EntityID; }

				entt::entity GetEntity() const { return m_EntityID; }
				GameScene* GetScene() const { return m_Scene; }

			private:
				entt::entity m_EntityID;
				GameScene* m_Scene;
		};

	}
	
}
