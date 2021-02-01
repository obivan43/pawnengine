#include "pch.h"
#include "Application.h"

namespace pawn {
	
	Application::Application() :
	m_isRunning(true),
	m_Fps(0),
	m_Window(pawn::WinAPIWindow::Instance(std::wstring(L"Pawn WinAPIWindow"), 800, 600)) {
		m_Clock.Reset();

#ifdef PAWN_DIRECTX11
		m_GraphicsContext = std::make_shared<pawn::DirectX11Context>();
		m_GraphicsAPI = std::make_unique<pawn::DirectX11API>();
#else
		m_GraphicsContext = std::make_shared<pawn::GraphicsContext>();
		m_GraphicsAPI = std::make_unique<pawn::GraphicsAPI>();
#endif
		m_GraphicsContext->Initialize(m_Window);
		m_GraphicsAPI->SetContext(m_GraphicsContext);
	}

	void Application::Run() {
		uint32_t fpsCounter = 0;
		float fpsTime = 0.0f;
		
		m_GraphicsAPI->SetClearColor(0.1f, 0.1f, 0.1f);
		while (m_isRunning) {
			m_Clock.Tick();
			float time = m_Clock.TotalTime();
			const float deltaTime =  m_Clock.DeltaTime();

			fpsCounter++;
			fpsTime += deltaTime;
			if (fpsTime >= 1.0f) {
				m_Fps = fpsCounter;

				fpsTime = 0.0f;
				fpsCounter = 0;

				std::cout << m_Fps << std::endl;
			}

			m_GraphicsAPI->Clear();
			
			m_Window.Update();
			m_GraphicsContext->SwapBuffers();

			if(m_Window.IsClosed()) {
				m_isRunning = false;
			}
		}
	}
	
}
