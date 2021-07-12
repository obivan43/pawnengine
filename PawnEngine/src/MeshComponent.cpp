#include "pch.h"
#include "MeshComponent.h"

namespace pawn {

	MeshComponent::MeshComponent(const std::shared_ptr<pawn::GraphicsMesh>& mesh, const std::string& meshPath) : Mesh(mesh), MeshPath(meshPath) {};

}