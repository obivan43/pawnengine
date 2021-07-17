#include "MeshManager.h"

#include "PawnGraphics/graphics/GraphicsInputLayout.h"
#include "PawnGraphics/graphics/GraphicsBuffer.h"
#include "PawnGraphics/graphics/data/GraphicsMesh.h"

#include "PawnUtils/utils/logger/Logger.h"

namespace pawn {

	bool MeshManager::HasMeshByPath(const std::string& path) {
		return m_MeshesMap[path].get() != nullptr;
	}

	bool MeshManager::UploadMesh(const std::string& name, const std::shared_ptr<GraphicsMesh>& mesh) {
		if (m_MeshesMap[name] != nullptr) {
			CONSOLE_WARN("MeshManager: mesh with same name already exist")
			return false;
		}

		m_MeshesMap[name] = mesh;

		return true;
	}

	bool MeshManager::UploadMeshFromFile(std::shared_ptr<GraphicsContext>& context, std::shared_ptr<GraphicsShader>& shader, const std::string& filename) {
		static const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float3 },
			{ "Normal", GraphicsInputElementType::Float3 },
			{ "TextureCoordinate", GraphicsInputElementType::Float2 }
		};

		if (m_MeshesMap[filename] != nullptr) {
			CONSOLE_WARN("MeshManager: mesh with same name already exist")
			return false;
		}

		bool result = m_MeshLoader.LoadModel(filename.c_str());
		if (!result) {
			CONSOLE_WARN("MeshManager: mesh loading corrupted")
			return result;
		}

		std::vector<math::Vertex>& vertices = m_MeshLoader.GetVertexData();
		std::vector<uint16_t>& indices = m_MeshLoader.GetIndexData();

		std::shared_ptr<GraphicsBuffer> vertexBuffer = GraphicsBuffer::Create(GraphicsBufferEnum::VertexBuffer);
		std::shared_ptr<GraphicsBuffer> indexBuffer = GraphicsBuffer::Create(GraphicsBufferEnum::IndexBuffer);
		std::shared_ptr<GraphicsInputLayout> inputLayout = GraphicsInputLayout::Create();

		vertexBuffer->Init(context, vertices.data(), static_cast<uint32_t>(vertices.size()), sizeof(math::Vertex), GraphicsBufferUsageTypeEnum::StaticBuffer);
		vertexBuffer->Bind(context);

		indexBuffer->Init(context, indices.data(), static_cast<uint32_t>(indices.size()), sizeof(uint16_t), GraphicsBufferUsageTypeEnum::StaticBuffer);
		indexBuffer->Bind(context);

		inputLayout->Init(context, inputElements, shader->GetVertexShaderInfo());

		m_MeshesMap[filename].reset(new GraphicsMesh(vertexBuffer, indexBuffer, inputLayout));

		return true;
	}

	const std::shared_ptr<GraphicsMesh>& MeshManager::GetMeshByPath(const std::string& path) {
		return m_MeshesMap[path];
	}

}
