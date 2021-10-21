#pragma once

#include "ApiHandler.h"

#include <memory>
#include <unordered_map>

namespace pawn::network {

	class Api {

		public:
			Api() = delete;
			Api(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network);

			Api(const Api& other) = delete;
			Api(Api&& other) noexcept = delete;

			Api& operator=(const Api& other) = delete;
			Api& operator=(Api&& other) noexcept = delete;
			
			void Handle(std::vector<int8_t>& data);

		private:
			std::unordered_map<std::string, std::shared_ptr<ApiHandler>> m_Mappings;

	};

}
