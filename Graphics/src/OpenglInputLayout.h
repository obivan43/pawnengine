#pragma once

#include "GraphicsInputLayout.h"

#ifdef PAWN_OPENGL

namespace pawn {

	class OpenglInputLayout : public GraphicsInputLayout {

		public:
			OpenglInputLayout();
			OpenglInputLayout(const OpenglInputLayout& other) = default;
			OpenglInputLayout(OpenglInputLayout&& other) noexcept = default;

			OpenglInputLayout& operator=(const OpenglInputLayout& other) = default;
			OpenglInputLayout& operator=(OpenglInputLayout&& other) noexcept = default;

			~OpenglInputLayout();

			void Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements, void* shaderData = nullptr) override;
			void Bind(std::shared_ptr<GraphicsContext>& context) override;

			uint32_t GetInputLayout() const { return m_InputLayout; }

			static uint32_t  GraphicsInputElementTypeToOpenglType(GraphicsInputElementType type);

		private:
			uint32_t m_InputLayout;
	};

}

#endif
