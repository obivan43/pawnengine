#include "pch.h"
#include "Application.h"
#include "Layer.h"

#ifdef PAWN_DIRECTX11
#include "DirectX11Layer.h"
#elif PAWN_OPENGL
#include "OpenGLLayer.h"
#endif


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
		const std::shared_ptr<pawn::Layer> layer(new DirectX11Layer());
#elif PAWN_OPENGL
		m_GraphicsContext = std::make_shared<pawn::OpenglContext>();
		m_GraphicsAPI = std::make_shared<pawn::OpenglAPI>();
		const std::shared_ptr<pawn::Layer> layer(new OpenGLLayer());
#else
		m_GraphicsContext = std::make_shared<pawn::GraphicsContext>();
		m_GraphicsAPI = std::make_shared<pawn::GraphicsAPI>();
		const std::shared_ptr<pawn::Layer> layer(new Layer());
#endif
		bool result = m_GraphicsContext->Init(m_Window);

		if(!result) {
			exit(-1);
		}
		
		m_GraphicsAPI->SetContext(m_GraphicsContext);
		m_LayerList.PushLayer(layer);
	}

	void Application::Run() {
		for (const std::shared_ptr<Layer>& layer : m_LayerList) {
			m_Window.AddObserver(layer.get());
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

				spdlog::get("console")->info("FPS: {}", m_Fps);
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

		m_LayerList.Clear();
	}

	void Application::HandleEvent(Event& e) {
		if (e.GetType() == EventTypeEnum::WindowClose) {
			m_isRunning = false;
		}
	}
	
}
