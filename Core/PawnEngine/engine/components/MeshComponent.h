#pragma once

#include "PawnGraphics/graphics/data/GraphicsMesh.h"

#include <memory>

namespace pawn {

	namespace engine {

		struct MeshComponent {

			MeshComponent() = default;
			MeshComponent(const std::shared_ptr<graphics::GraphicsMesh>& mesh, const std::string& meshPath = std::string());
			MeshComponent(const MeshComponent& other) = default;
			MeshComponent(MeshComponent&& other) noexcept = default;

			MeshComponent& operator=(const MeshComponent& other) = default;
			MeshComponent& operator=(MeshComponent&& other) noexcept = default;

			operator std::shared_ptr<graphics::GraphicsMesh>& () { return Mesh; }
			operator const std::shared_ptr<graphics::GraphicsMesh>& () const { return Mesh; }

			std::shared_ptr<graphics::GraphicsMesh> Mesh;
			std::string MeshName;
		};

	}

}
