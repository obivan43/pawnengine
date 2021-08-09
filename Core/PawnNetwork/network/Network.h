#pragma once

#include "PawnSystem/system/windows/WindowsAPI.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <cstdint>
#include <vector>

namespace pawn::network {
#define DEFAULT_BUFLEN 512

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
			SOCKET ClientSocket;
			std::vector<int8_t> recvbuf;
	};
}