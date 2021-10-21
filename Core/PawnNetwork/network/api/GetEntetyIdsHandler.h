#pragma once

#include "ApiHandler.h"

namespace pawn::network {

	class GetEntetyIdsHandler final : public ApiHandler {

		public:
			GetEntetyIdsHandler() = delete;
			GetEntetyIdsHandler(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network);

			GetEntetyIdsHandler(const GetEntetyIdsHandler& other) = delete;
			GetEntetyIdsHandler(GetEntetyIdsHandler&& other) noexcept = delete;

			GetEntetyIdsHandler& operator=(const GetEntetyIdsHandler& other) = delete;
			GetEntetyIdsHandler& operator=(GetEntetyIdsHandler&& other) noexcept = delete;

			void Handle() override final;

	};

}
