#pragma once

#include "GameScene.h"

#include <utility>

namespace pawn::engine {
	
	class GameEntity {

		public:
			GameEntity();
			GameEntity(entt::entity id, GameScene* scene);

			GameEntity(const GameEntity& other) = default;
			GameEntity(GameEntity&& other) noexcept = default;

			GameEntity& operator=(const GameEntity& other) = default;
			GameEntity& operator=(GameEntity&& other) noexcept = default;

			inline bool IsNull() const noexcept { return m_EntityID == entt::null; }

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

			inline bool operator==(const GameEntity& other) const noexcept {
				return m_EntityID == other.m_EntityID;
			}

			inline operator entt::entity() const noexcept { return m_EntityID; }

			inline entt::entity GetEntity() const noexcept { return m_EntityID; }
			inline GameScene* GetScene() noexcept { return m_Scene; }

		private:
			entt::entity m_EntityID;
			GameScene* m_Scene;
	};

}
