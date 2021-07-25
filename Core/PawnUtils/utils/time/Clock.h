#pragma once

#include <cstdint>

namespace pawn {

	namespace utils {

		class Clock {
	
			public:
				Clock();
				Clock(const Clock& other) = default;

				static float TimeStampToSeconds(int64_t timestamp);
				static int64_t TimeStamp();

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

}
