#pragma once

#include <cstdint>
#include <stdlib.h>
#include <string>
#include <vector>

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
			int Send(const std::string& buffer);

			std::vector<int8_t>& Data();

		private:
			unsigned long long* m_ClientSocket;
			std::vector<int8_t> m_Buffer;
	};

}
