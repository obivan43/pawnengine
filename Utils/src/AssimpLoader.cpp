#include "pch.h"
#include "AssimpLoader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace pawn {

	void AssimpLoader::LoadModel(const std::string& file) {
		Assimp::Importer importer;

		/*const aiScene* scene = importer.ReadFile(file,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType
		);*/
	}

}
