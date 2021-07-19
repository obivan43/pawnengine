#include "MeshComponent.h"

namespace pawn {

	namespace engine {

		MeshComponent::MeshComponent(const std::shared_ptr<graphics::GraphicsMesh>& mesh, const std::string& meshPath) : Mesh(mesh), MeshName(meshPath) {};

	}

}
