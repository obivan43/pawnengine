#include "Network.h"

namespace pawn::network {

	Network::Network() : m_ClientSocket(INVALID_SOCKET) {
        m_Buffer.reserve(PAWN_DEFAULT_BUFLEN);
    }

	int Network::Init() {
        WSADATA wsaData;

        addrinfo* result = nullptr;
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            return 1;
        }

        addrinfo hints{};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        PCSTR port = PAWN_DEFAULT_PORT;
        iResult = getaddrinfo(nullptr, port, &hints, &result);
        if (iResult != 0) {
            WSACleanup();
            return 1;
        }

        SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET) {
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }

        iResult = bind(ListenSocket, result->ai_addr, static_cast<int>(result->ai_addrlen));
        if (iResult == SOCKET_ERROR) {
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        freeaddrinfo(result);

        iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        m_ClientSocket = accept(ListenSocket, nullptr, nullptr);
        if (m_ClientSocket == INVALID_SOCKET) {
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        closesocket(ListenSocket);

        return 0;
	}

    int Network::Shutdown() {
        int iResult = shutdown(m_ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            closesocket(m_ClientSocket);
            WSACleanup();
            return 1;
        }

        closesocket(m_ClientSocket);
        WSACleanup();
        return 0;
    }

    int Network::Receive() {
        return recv(m_ClientSocket, reinterpret_cast<char*>(m_Buffer.data()), static_cast<int>(m_Buffer.size()), 0);
    }

    int Network::Send(std::vector<int8_t>& buffer) {
        return send(m_ClientSocket, reinterpret_cast<char*>(buffer.data()), static_cast<int>(buffer.size()), 0);
    }

    int8_t* Network::Data() {
        return m_Buffer.data();
    }
}