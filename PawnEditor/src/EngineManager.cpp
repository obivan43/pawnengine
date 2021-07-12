#include "pch.h"
#include "EngineManager.h"

namespace impl {

	EngineManager::EngineManager(pawn::Engine* engine) : m_Engine(engine) {}

	void EngineManager::OnEntityMeshModified(pawn::GameEntity entity) {
		if (!entity.IsNull()) {
			pawn::MeshComponent& meshComponent = entity.GetComponent<pawn::MeshComponent>();
			
			if (!m_Engine->HasMeshByPath(meshComponent.MeshPath)) {
				m_Engine->UploadMeshFromFile(meshComponent.MeshPath);
			}

			meshComponent.Mesh = m_Engine->GetMeshByPath(meshComponent.MeshPath);
		}
	}

}