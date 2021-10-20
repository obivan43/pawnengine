#include "MeshComponent.h"

namespace pawn::engine {

	MeshComponent::MeshComponent(const std::shared_ptr<Mesh>& mesh, const std::string& meshPath) : MeshData(mesh), MeshName(meshPath) {};

}
