#pragma once

namespace pawn {

	class Layer : public Observer {
		
		public:
			virtual void OnInit();
			virtual void OnUpdate(Clock clock);
			virtual void OnRelease();
	};
	
}


