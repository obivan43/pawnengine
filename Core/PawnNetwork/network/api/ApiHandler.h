#pragma once

#include "PawnEngine/engine/Engine.h"
#include "PawnNetwork/network/Network.h"

#include <memory>

namespace pawn::network {

	class ApiHandler {

		public:
			ApiHandler() = delete;
			ApiHandler(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network);

			ApiHandler(const ApiHandler& other) = delete;
			ApiHandler(ApiHandler&& other) noexcept = delete;

			ApiHandler& operator=(const ApiHandler& other) = delete;
			ApiHandler& operator=(ApiHandler&& other) noexcept = delete;

			virtual void Handle() = 0;

		protected:
			std::shared_ptr<engine::Engine> m_Engine;
			std::shared_ptr<Network> m_Network;

	};

}
