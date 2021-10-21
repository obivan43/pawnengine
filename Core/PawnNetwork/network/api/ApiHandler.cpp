#include "ApiHandler.h"

namespace pawn::network {

	ApiHandler::ApiHandler(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network)
		: m_Engine(engine), m_Network(network) {}

}
