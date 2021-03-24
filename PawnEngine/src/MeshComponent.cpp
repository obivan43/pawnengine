#include "pch.h"
#include "MeshComponent.h"

namespace pawn {

	MeshComponent::MeshComponent(const std::shared_ptr<pawn::Mesh>& mesh, const std::string& meshPath) : Mesh(mesh), MeshPath(meshPath) {};

}