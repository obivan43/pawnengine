#pragma once

#include "Macros.h"

#include <cstdint>

namespace pawn {

	class Clock {
		
		public:
			Clock();
		
			float Time() const;
			float DeltaTime() const;
			float TotalTime() const;

			void Reset();
			void Start();
			void Stop();
			void Tick();

		private:
			double m_SecondsPerCount;
			double m_DeltaTime;

			int64_t m_BaseTime;
			int64_t m_PausedTime;
			int64_t m_StopTime;
			int64_t m_PrevTime;
			int64_t m_CurrentTime;

			bool m_Stopped;
	};

}
