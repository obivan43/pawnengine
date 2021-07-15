#pragma once

#include "PawnGraphics/src/GraphicsMesh.h"

#include <memory>

namespace pawn {

	struct MeshComponent {

		MeshComponent() = default;
		MeshComponent(const std::shared_ptr<pawn::GraphicsMesh>& mesh, const std::string& meshPath = std::string());
		MeshComponent(const MeshComponent& other) = default;
		MeshComponent(MeshComponent&& other) noexcept = default;

		MeshComponent& operator=(const MeshComponent& other) = default;
		MeshComponent& operator=(MeshComponent&& other) noexcept = default;

		operator std::shared_ptr<pawn::GraphicsMesh>& () { return Mesh; }
		operator const std::shared_ptr<pawn::GraphicsMesh>& () const { return Mesh; }

		std::shared_ptr<pawn::GraphicsMesh> Mesh;
		std::string MeshPath;
	};

}