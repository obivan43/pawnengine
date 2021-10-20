#include "Api.h"
#include "GetEntetyIdsHandler.h"

namespace pawn::network {

	Api::Api(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network) {
		m_mappings["GetEntityIds"] = std::make_shared<GetEntetyIdsHandler>(engine, network);
	}

	void Api::Handle(std::vector<int8_t>& data) {
		std::string request(data.begin(), data.end());

		nlohmann::json j;
		nlohmann::json result = j.parse(request);

		std::string str;
		j.at("Request").get_to(str);

		m_mappings[str]->Handle();
	}
}
