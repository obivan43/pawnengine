#include "GetEntetyIdsHandler.h"

namespace pawn::network {

	GetEntetyIdsHandler::GetEntetyIdsHandler(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network)
		: ApiHandler(engine, network) {}

	void GetEntetyIdsHandler::Handle() {
		std::string response = m_engine->GetJsonSerializer()->JsonEntityIds().dump();

		m_network->Send(response);
	}

}
