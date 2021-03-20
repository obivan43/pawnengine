#pragma once

#include "PawnGraphics/src/Mesh.h"

#include <memory>

namespace pawn {

	struct MeshComponent {

		MeshComponent() = default;
		MeshComponent(const std::shared_ptr<pawn::Mesh>& mesh);
		MeshComponent(const MeshComponent& other) = default;
		MeshComponent(MeshComponent&& other) noexcept = default;

		MeshComponent& operator=(const MeshComponent& other) = default;
		MeshComponent& operator=(MeshComponent&& other) noexcept = default;

		operator std::shared_ptr<pawn::Mesh>& () { return Mesh; }
		operator const std::shared_ptr<pawn::Mesh>& () const { return Mesh; }

		std::shared_ptr<pawn::Mesh> Mesh;
	};

}