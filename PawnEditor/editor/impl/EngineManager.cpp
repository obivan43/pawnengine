#include "EngineManager.h"

namespace impl {

	EngineManager::EngineManager(pawn::engine::Engine* engine) : m_Engine(engine) {}

	void EngineManager::OnEntityMeshModified(pawn::engine::GameEntity entity) {
		if (!entity.IsNull()) {
			pawn::engine::MeshComponent& meshComponent = entity.GetComponent<pawn::engine::MeshComponent>();
			
			if (!m_Engine->HasMeshByPath(meshComponent.MeshPath)) {
				m_Engine->UploadMeshFromFile(meshComponent.MeshPath);
			}

			meshComponent.Mesh = m_Engine->GetMeshByPath(meshComponent.MeshPath);
		}
	}

}