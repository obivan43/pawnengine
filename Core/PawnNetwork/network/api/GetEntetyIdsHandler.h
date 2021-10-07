#pragma once

#include "ApiHandler.h"

namespace pawn::network {

	class GetEntetyIdsHandler : public ApiHandler {

		public:
			GetEntetyIdsHandler(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network);
			void Handle() override;

	};

}
