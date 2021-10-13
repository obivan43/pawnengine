#include "EngineGlobals.h"

namespace pawn {

	namespace engine {

		static bool g_ShouldHandleMouseInEngineScripts = true;

		bool GetMouseHandlingStateInScripts() {
			return g_ShouldHandleMouseInEngineScripts;
		}

		void SetMouseHandlingStateInScripts(bool state) {
			g_ShouldHandleMouseInEngineScripts = state;
		}

	}

}