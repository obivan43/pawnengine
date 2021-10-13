#include "EngineManager.h"

namespace editor {

	namespace impl {

		EngineManager::EngineManager(pawn::engine::Engine* engine) : m_Engine(engine) {}

		pawn::engine::Engine* EngineManager::GetEngine() {
			return m_Engine;
		}

		void EngineManager::OnEntityMeshModified(pawn::engine::GameEntity entity) {
			if (!entity.IsNull()) {
				pawn::engine::MeshComponent& meshComponent = entity.GetComponent<pawn::engine::MeshComponent>();

				if (!m_Engine->HasMeshByName(meshComponent.MeshName)) {
					m_Engine->UploadMeshFromFile(meshComponent.MeshName);
				}

				meshComponent.Mesh = m_Engine->GetMeshByName(meshComponent.MeshName);
			}
		}

		void EngineManager::OnEntityTexture2DModified(pawn::engine::GameEntity entity) {
			if (!entity.IsNull()) {
				pawn::engine::Texture2DComponent& texture2DComponent = entity.GetComponent<pawn::engine::Texture2DComponent>();

				if (!m_Engine->HasTextureByName(texture2DComponent.TextureName)) {
					m_Engine->UploadTextureFromFile(texture2DComponent.TextureName);
				}

				texture2DComponent.Texture = m_Engine->GetTextureByName(texture2DComponent.TextureName);
			}
		}

	}

}
