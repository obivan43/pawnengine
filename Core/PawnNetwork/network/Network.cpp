#include "Network.h"

namespace pawn::network {
	Network::Network() : ClientSocket(INVALID_SOCKET) {
        recvbuf.reserve(DEFAULT_BUFLEN);
    }

	int Network::Init() {
        const int32_t BufLen = 512;
        const char* Port = "53818";

        WSADATA wsaData;
        int iResult;

        struct addrinfo* result = NULL;
        struct addrinfo hints;

        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            return 1;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        iResult = getaddrinfo(NULL, Port, &hints, &result);
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

        iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
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

        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        closesocket(ListenSocket);
        return 0;
	}

    int Network::Shutdown() {
        int iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

        closesocket(ClientSocket);
        WSACleanup();
        return 0;
    }

    int Network::Receive() {
        return recv(ClientSocket, reinterpret_cast<char*>(recvbuf.data()), recvbuf.size(), 0);
    }

    int Network::Send(std::vector<int8_t>& buffer) {
        return send(ClientSocket, reinterpret_cast<char*>(buffer.data()), buffer.size(), 0);
    }

    int8_t* Network::Data() {
        return recvbuf.data();
    }
}