#pragma once

#include "PawnEngine/engine/geometry/Mesh.h"

#include <memory>

namespace pawn {

	namespace engine {

		struct MeshComponent {

			MeshComponent() = default;
			MeshComponent(const std::shared_ptr<Mesh>& mesh, const std::string& meshPath = std::string());
			MeshComponent(const MeshComponent& other) = default;
			MeshComponent(MeshComponent&& other) noexcept = default;

			MeshComponent& operator=(const MeshComponent& other) = default;
			MeshComponent& operator=(MeshComponent&& other) noexcept = default;

			operator std::shared_ptr<Mesh>& () { return MeshData; }
			operator const std::shared_ptr<Mesh>& () const { return MeshData; }

			std::shared_ptr<Mesh> MeshData;
			std::string MeshName;
		};

	}

}
