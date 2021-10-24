#pragma once

#include "PawnEngine/engine/data/Mesh.h"

#include <memory>

namespace pawn::engine {

	struct MeshComponent {

		MeshComponent() = default;
		MeshComponent(const std::shared_ptr<Mesh>& mesh, const std::string& meshName = std::string());

		MeshComponent(const MeshComponent& other) = default;
		MeshComponent(MeshComponent&& other) noexcept = default;

		MeshComponent& operator=(const MeshComponent& other) = default;
		MeshComponent& operator=(MeshComponent&& other) noexcept = default;

		inline operator std::shared_ptr<Mesh>& () noexcept { return MeshData; }
		inline operator const std::shared_ptr<Mesh>& () const noexcept { return MeshData; }

		std::shared_ptr<Mesh> MeshData;
		std::string MeshName;
	};

}
