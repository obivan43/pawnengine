#pragma once

namespace pawn {
	
	class Application : public Singleton<Application>, public Observer {
		
		public:
			Application();
		
			void Run();

			virtual void HandleEvent(const Event& e) override;
		
			bool GetIsRunning() const { return m_isRunning; }
			uint32_t GetFps() const { return m_Fps; }
			const pawn::Clock& GetClock() const { return m_Clock; }
			const pawn::Window& GetWindow() const { return m_Window; }
			std::shared_ptr<pawn::GraphicsContext>& GetGraphicsContext() { return m_GraphicsContext; }
	
		private:
			bool m_isRunning;
			uint32_t m_Fps;
			pawn::Clock m_Clock;
			pawn::Window& m_Window;

			std::unique_ptr<pawn::GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<pawn::GraphicsContext> m_GraphicsContext;
	};
	
}
