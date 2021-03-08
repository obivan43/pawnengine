#include "pch.h"
#include "Application.h"
#include "DefaultLayer.h"

namespace pawn {
	
	Application::Application() :
	m_isRunning(true),
	m_Fps(0),
	m_Window(pawn::WinAPIWindow::Instance(std::wstring(L"Pawn WinAPIWindow"), 1280, 1024)) {
		m_Window.AddObserver(this);
		
		m_Clock.Reset();

		m_GraphicsAPI = GraphicsAPI::Create();
		m_GraphicsContext = GraphicsContext::Create();

		bool result = m_GraphicsContext->Init(m_Window);

		if(!result) {
			exit(-1);
		}
		
		m_GraphicsAPI->SetContext(m_GraphicsContext);
	}

	void Application::Run() {
		const std::shared_ptr<pawn::Layer> layer(new DefaultLayer());
		m_LayerList.PushLayer(layer);
		
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

			KeyboardInputManager& keyboard = m_Window.GetKeyBoardInputManager();
			while(!keyboard.IsKeyBufferEmpty()) {
				
				std::optional<std::shared_ptr<Event>> optionalEvent = keyboard.ReadKeyFromBuffer();
				if(optionalEvent.has_value()) {
					std::shared_ptr<Event>& keyboardEvent = optionalEvent.value();
					
					for (const std::shared_ptr<Layer>& layer : m_LayerList) {
						if(!keyboardEvent->GetIsHandeled()) {
							layer->HandleEvent(*keyboardEvent);
						}
					}
				}
				
			}

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
