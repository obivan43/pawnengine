#pragma once

#include "OpenglBufferBase.h"

#ifdef PAWN_OPENGL

namespace pawn {

	class OpenglConstantBuffer : public OpenglBufferBase {

	public:
		OpenglConstantBuffer();
		OpenglConstantBuffer(const OpenglConstantBuffer& other) = default;
		OpenglConstantBuffer(OpenglConstantBuffer&& other) noexcept = default;

		OpenglConstantBuffer& operator=(const OpenglConstantBuffer& other) = default;
		OpenglConstantBuffer& operator=(OpenglConstantBuffer&& other) noexcept = default;

		void InitLocation(
			std::shared_ptr<GraphicsContext>& context,
			std::shared_ptr<GraphicsShader>& shader,
			const std::string& name,
			uint32_t index = 0
		) override;

		void Init(
			std::shared_ptr<GraphicsContext>& context,
			void* data,
			uint32_t numVertices,
			uint32_t sizeofBufferDataType,
			GraphicsBufferUsageTypeEnum type = GraphicsBufferUsageTypeEnum::DynamicBuffer
		) override;
		
		void Bind(std::shared_ptr<GraphicsContext>& context) override;
		void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;
	
	private:
		uint32_t m_UniformIndex;
		uint32_t m_BindingIndex;
	};

}

#endif
