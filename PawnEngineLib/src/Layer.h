#pragma once

namespace pawn {

	class Layer : public Observer {
		
		public:
			Layer() = default;
			Layer(const Layer& other) = delete;
			Layer(Layer&& other) noexcept = default;
		
			Layer& operator=(const Layer& other) = delete;
			Layer& operator=(Layer&& other) noexcept = delete;

			virtual ~Layer() = default;
		
			virtual void OnInit();
			virtual void OnUpdate(Clock clock);
			virtual void OnRelease();
	};
	
}


