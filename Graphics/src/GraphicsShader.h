﻿#pragma once


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
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;

			virtual void* GetShader() { return nullptr; }
			virtual void* GetVertexShaderInfo() const { return nullptr; }
			virtual void* GetPixelShaderInfo() const { return nullptr; }

			static std::shared_ptr<GraphicsShader> Create();
	};

}
