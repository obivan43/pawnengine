#include "Api.h"

#include "GetEntetyIdsHandler.h"

namespace pawn::network {

	Api::Api(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network) {
		m_Mappings["GetEntityIds"] = std::make_shared<GetEntetyIdsHandler>(engine, network);
	}

	void Api::Handle(std::vector<int8_t>& data) {
		std::string request(data.begin(), data.end());

		nlohmann::json json;
		nlohmann::json result = json.parse(request);

		std::string str;
		json.at("Request").get_to(str);

		m_Mappings[str]->Handle();
	}
}
