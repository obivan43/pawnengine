#pragma once

#include "GraphicsBuffer.h"

#ifdef PAWN_OPENGL

namespace pawn {

	class OpenglConstantBuffer : public GraphicsBuffer {

	public:
		OpenglConstantBuffer();
		OpenglConstantBuffer(const OpenglConstantBuffer& other) = default;
		OpenglConstantBuffer(OpenglConstantBuffer&& other) noexcept = default;

		OpenglConstantBuffer& operator=(const OpenglConstantBuffer& other) = default;
		OpenglConstantBuffer& operator=(OpenglConstantBuffer&& other) noexcept = default;

		~OpenglConstantBuffer();

		void InitLocation(
			std::shared_ptr<GraphicsContext>& context,
			std::shared_ptr<GraphicsShader>& shader,
			const std::string& name,
			uint32_t index = 0
		) override;
		
		void Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t sizeofBufferDataType) override;
		void Bind(std::shared_ptr<GraphicsContext>& context) override;

		void* GetBuffer() const override { return reinterpret_cast<void*>(m_Buffer); }
		uint32_t GetBufferSize() const override { return m_BufferSize; }
		uint32_t GetStride() const override { return m_Stride; }

	private:
		uint32_t m_Buffer;
		uint32_t m_BufferSize;
		uint32_t m_Stride;
		uint32_t m_UniformIndex;
		uint32_t m_BindingIndex;
	};

}

#endif
