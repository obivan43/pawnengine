#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <cstdint>
#include <vector>

#include "PawnSystem/system/windows/WindowsAPI.h"

namespace pawn::network {

#define PAWN_DEFAULT_BUFLEN 1024
#define PAWN_DEFAULT_PORT "53818";

	class Network {

		public:
			Network();
			Network(const Network& other) = delete;
			Network(Network&& other) noexcept = delete;

			Network& operator=(const Network& other) = delete;
			Network& operator=(Network&& other) noexcept = delete;

			int Init();
			int Shutdown();

			int Receive();
			int Send(std::vector<int8_t>& buffer);

			int8_t* Data();

		private:
			SOCKET m_ClientSocket;
			std::vector<int8_t> m_Buffer;
	};

}
