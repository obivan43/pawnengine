#include "DirectX11DebugInfoManager.h"

namespace pawn::graphics {

	DirectX11DebugInfoManager::DirectX11DebugInfoManager() {
		typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

		const HMODULE dxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		if (dxgiDebug == nullptr) {
			throw std::exception("Unable to load dxgidebug.dll");
		}

		const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
			reinterpret_cast<void*>(GetProcAddress(dxgiDebug, "DXGIGetDebugInterface"))
		);

		if (DxgiGetDebugInterface == nullptr) {
			throw std::exception("Unable to create DXGIInterface");
		}

		DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &m_DXGIInfoQueue);
	}

	DirectX11DebugInfoManager& DirectX11DebugInfoManager::Instance() {
		static DirectX11DebugInfoManager infoManager;
		return infoManager;
	}

	void DirectX11DebugInfoManager::Set() {
		next = m_DXGIInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	}

	std::vector<std::string> DirectX11DebugInfoManager::GetMessages() const {
		std::vector<std::string> messages;
		const auto end = m_DXGIInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
		for (auto i = next; i < end; i++) {
			HRESULT hr;

			SIZE_T messageLength;
			hr = m_DXGIInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength);
			if (FAILED(hr)) {
				throw std::exception("Unable to get debug message length");
			}

			auto bytes = std::make_unique<byte[]>(messageLength);
			auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());

			hr = m_DXGIInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength);
			if (FAILED(hr)) {
				throw std::exception("Unable to get debug message");
			}
			messages.emplace_back(pMessage->pDescription);
		}

		return messages;
	}

}
