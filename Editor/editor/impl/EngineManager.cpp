#include "EngineManager.h"

namespace editor {

	namespace impl {

		EngineManager::EngineManager(pawn::engine::Engine* engine) : m_Engine(engine) {}

		void EngineManager::OnEntityMeshModified(pawn::engine::GameEntity entity) {
			if (!entity.IsNull()) {
				pawn::engine::MeshComponent& meshComponent = entity.GetComponent<pawn::engine::MeshComponent>();

				if (!m_Engine->HasMeshByName(meshComponent.MeshName)) {
					m_Engine->UploadMeshFromFile(meshComponent.MeshName);
				}

				meshComponent.Mesh = m_Engine->GetMeshByName(meshComponent.MeshName);
			}
		}

	}

}
