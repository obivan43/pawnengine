#pragma once

#include "PawnGraphics/graphics/directx/Directx11Context.h"

#include <vector>
#include <string>
#include <exception>

#ifdef PAWN_DIRECTX11

namespace pawn::graphics {

	class DirectX11Exception : public std::exception {

		public:
			DirectX11Exception(HRESULT result, const char* file, unsigned int line, const char* expression, const std::vector<std::string>& messages);
			DirectX11Exception(const DirectX11Exception& other) = default;
			DirectX11Exception(DirectX11Exception&& other) noexcept = default;

			DirectX11Exception& operator=(const DirectX11Exception& other) = default;
			DirectX11Exception& operator=(DirectX11Exception&& other) noexcept = default;

			const char* what() const noexcept;

		private:
			HRESULT m_Result;
			uint32_t m_Line;

			std::string m_File;
			std::string m_Expression;
			std::string m_Info;
			mutable std::string m_WhatCache;
	};

}

#endif