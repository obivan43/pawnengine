#include "ApiHandler.h"

namespace pawn::network {
	ApiHandler::ApiHandler(std::shared_ptr<engine::Engine>& engine, std::shared_ptr<Network>& network) : m_engine(engine), m_network(network) {}
}