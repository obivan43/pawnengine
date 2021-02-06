#include "pch.h"
#include "DefaultLayer.h"
#include "Application.h"

namespace pawn {

	void DefaultLayer::OnInit() {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();
	}
	
	void DefaultLayer::OnUpdate(Clock clock) {
		
	}
	
	void DefaultLayer::OnRelease() {}
	
}
