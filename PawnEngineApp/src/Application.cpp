#include "pch.h"
#include "Application.h"

#include "DefaultLayer.h"
#include "Layer.h"

namespace pawn {
	
	Application::Application() :
	m_isRunning(true),
	m_Fps(0),
	m_Window(pawn::WinAPIWindow::Instance(std::wstring(L"Pawn WinAPIWindow"), 800, 600)) {
		m_Window.AddObserver(this);
		
		m_Clock.Reset();

#ifdef PAWN_DIRECTX11
		m_GraphicsContext = std::make_shared<pawn::DirectX11Context>();
		m_GraphicsAPI = std::make_shared<pawn::DirectX11API>();
#else
		m_GraphicsContext = std::make_shared<pawn::GraphicsContext>();
		m_GraphicsAPI = std::make_shared<pawn::GraphicsAPI>();
#endif
		m_GraphicsContext->Initialize(m_Window);
		m_GraphicsAPI->SetContext(m_GraphicsContext);

		const std::shared_ptr<pawn::Layer> layer(new DefaultLayer());
		m_LayerList.PushLayer(layer);
	}

	void Application::Run() {
		for (const std::shared_ptr<Layer>& layer : m_LayerList) {
			layer->OnInit();
		}
		
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
			}

			m_GraphicsAPI->Clear();

			for (const std::shared_ptr<Layer>& layer : m_LayerList) {
				layer->OnUpdate(m_Clock);
			}
			
			m_Window.Update();
			m_GraphicsContext->SwapBuffers();
		}

		for (const std::shared_ptr<Layer>& layer : m_LayerList) {
			layer->OnRelease();
		}
	}

	void Application::HandleEvent(const Event& e) {
		switch (e.GetType()) {
			case EventTypeEnum::WindowClose:
				m_isRunning = false;
				break;
			default:
				break;
		}	
	}
	
}
