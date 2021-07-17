#include "MeshComponent.h"

namespace pawn {

	MeshComponent::MeshComponent(const std::shared_ptr<graphics::GraphicsMesh>& mesh, const std::string& meshPath) : Mesh(mesh), MeshPath(meshPath) {};

}
