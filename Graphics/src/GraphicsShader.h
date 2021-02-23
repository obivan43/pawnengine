#pragma once


#include "GraphicsBindableResource.h"

namespace pawn {

	class GraphicsShader : public GraphicsBindableResource {

		public:
			GraphicsShader() = default;
			GraphicsShader(const GraphicsShader& other) = default;
			GraphicsShader(GraphicsShader&& other) noexcept = default;

			GraphicsShader& operator=(const GraphicsShader& other) = default;
			GraphicsShader& operator=(GraphicsShader&& other) noexcept = default;

			virtual ~GraphicsShader() = default;

			virtual bool InitVertexShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName);
			virtual bool InitPixelShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName);
			virtual bool Link();
			void Bind(std::shared_ptr<GraphicsContext>& context) override;

			virtual void* GetShader() const { return nullptr; }
	};

}
