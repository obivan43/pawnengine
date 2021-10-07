#pragma once

#include <unordered_map>
#include <memory>
#include "ApiHandler.h"

namespace pawn::network {

	class Api {

		public:

			Api(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network);
			void Handle(std::vector<int8_t>& data);

		private:
			std::unordered_map<std::string, std::shared_ptr<ApiHandler>> m_mappings;

	};

}
