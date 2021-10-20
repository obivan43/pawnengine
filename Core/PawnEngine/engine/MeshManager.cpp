#include "MeshManager.h"

#include "PawnGraphics/graphics/GraphicsInputLayout.h"
#include "PawnGraphics/graphics/GraphicsBuffer.h"
#include "PawnGraphics/graphics/data/GraphicsMesh.h"

#include "PawnUtils/utils/logger/Logger.h"

namespace pawn::engine {

	bool MeshManager::HasMeshByName(const std::string& name) {
		return m_MeshesMap[name].get() != nullptr;
	}

	bool MeshManager::UploadMesh(const std::string& name, const std::shared_ptr<Mesh>& mesh) {
		if (m_MeshesMap[name] != nullptr) {
			CONSOLE_WARN("MeshManager: mesh with same name already exist")
				return false;
		}

		m_MeshesMap[name] = mesh;

		return true;
	}

	bool MeshManager::UploadMeshFromFile(std::shared_ptr<graphics::GraphicsContext>& context, std::shared_ptr<graphics::GraphicsShader>& shader, const std::string& path) {
		std::string name = path.substr(path.find_last_of("/\\") + 1);

		if (m_MeshesMap[name] != nullptr) {
			CONSOLE_WARN("MeshManager: mesh with same name already exist")
				return false;
		}
		std::shared_ptr<Mesh> mesh = m_MeshLoader.LoadModel(path.c_str(), context, shader);
		if (mesh.get() == nullptr) {
			CONSOLE_ERROR("MeshManager: mesh loading corrupted")
				return false;
		}

		m_MeshesMap[name] = mesh;

		CONSOLE_INFO("MeshManager: Model loaded {}", path)

			return true;
	}

	const std::shared_ptr<Mesh>& MeshManager::GetMeshByName(const std::string& name) {
		return m_MeshesMap[name];
	}

}
