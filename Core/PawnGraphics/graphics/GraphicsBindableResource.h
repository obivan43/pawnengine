#pragma once

#include <memory>

namespace pawn::graphics {

	class GraphicsContext;

	class GraphicsBindableResource {

		public:
			GraphicsBindableResource() = default;
			GraphicsBindableResource(const GraphicsBindableResource& other) = default;
			GraphicsBindableResource(GraphicsBindableResource && other) noexcept = default;

			GraphicsBindableResource& operator=(const GraphicsBindableResource& other) = default;
			GraphicsBindableResource& operator=(GraphicsBindableResource&& other) noexcept = default;

			virtual void Bind(std::shared_ptr<GraphicsContext>& context) = 0;
			virtual void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) = 0;
			virtual void Unbind(std::shared_ptr<GraphicsContext>& context) = 0;
	};

}
