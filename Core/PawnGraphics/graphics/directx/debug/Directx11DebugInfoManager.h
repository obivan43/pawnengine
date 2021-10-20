#pragma once

#include "PawnGraphics/graphics/directx/Directx11Context.h"

#include <vector>
#include <string>
#include <exception>

#ifdef PAWN_DIRECTX11

#include <dxgidebug.h>

namespace pawn::graphics {

	class DirectX11DebugInfoManager {

			DirectX11DebugInfoManager();
			DirectX11DebugInfoManager(const DirectX11DebugInfoManager& other) = default;
			DirectX11DebugInfoManager(DirectX11DebugInfoManager&& other) noexcept = default;

			DirectX11DebugInfoManager& operator=(const DirectX11DebugInfoManager& other) = default;
			DirectX11DebugInfoManager& operator=(DirectX11DebugInfoManager&& other) noexcept = default;

		public:
			static DirectX11DebugInfoManager& Instance();

			void Set();
			std::vector<std::string> GetMessages() const;

		private:
			unsigned long long next = 0u;
			Microsoft::WRL::ComPtr<IDXGIInfoQueue> m_DXGIInfoQueue;
	};

}

#endif
