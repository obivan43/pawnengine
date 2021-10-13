#pragma once

#include <memory>

namespace pawn {

	namespace graphics {

		class GraphicsContext;

		class GraphicsBindableResource {

			public:
				virtual void Bind(std::shared_ptr<GraphicsContext>& context) = 0;
				virtual void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) = 0;
				virtual void Unbind(std::shared_ptr<GraphicsContext>& context) = 0;
		};

	}

}
