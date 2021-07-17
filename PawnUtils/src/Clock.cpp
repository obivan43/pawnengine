#include "pch.h"
#include "Clock.h"

#ifdef _WIN32

#include "PawnSystem/system/windows/WindowsAPI.h"

namespace pawn {

	Clock::Clock() :
	m_SecondsPerCount(0.0f), m_DeltaTime(-1.0f), m_BaseTime(0),
	m_PausedTime(0), m_StopTime(0), m_PrevTime(0), m_CurrentTime(0), m_Stopped(false) {
		int64_t countPerSecond = 0;
		QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countPerSecond));
		m_SecondsPerCount = 1.0 / static_cast<double>(countPerSecond);
	}

	int64_t Clock::TimeStamp() const {
		return m_CurrentTime;
	}

	float Clock::Time() const {
		return static_cast<float>(m_CurrentTime);
	}

	float Clock::DeltaTime() const {
		return static_cast<float>(m_DeltaTime);
	}


	float Clock::TotalTime() const {
		if(m_Stopped) {
			return static_cast<float>(
				static_cast<double>(((m_StopTime - m_PausedTime) - m_BaseTime)) * m_SecondsPerCount
			);
		}

		return static_cast<float>(
				static_cast<double>(((m_CurrentTime - m_PausedTime) - m_BaseTime)) * m_SecondsPerCount
		);
	}

	void Clock::Reset() {
		int64_t currentTime = 0;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));

		m_BaseTime = currentTime;
		m_PrevTime = currentTime;
		m_StopTime = 0;
		m_Stopped = false;
	}

	void Clock::Start() {
		int64_t currentTime = 0;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));
		
		if (m_Stopped) {
			m_PausedTime += (currentTime - m_StopTime);
			m_PrevTime = currentTime;
			m_StopTime = 0;
			m_Stopped = false;
		}
	}

	void Clock::Stop() {
		if(!m_Stopped) {
			int64_t currentTime = 0;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));
			m_StopTime = currentTime;
			m_Stopped = true;
		}
	}

	void Clock::Tick() {
		if(m_Stopped) {
			m_DeltaTime = 0.0;
			return;
		}

		int64_t currentTime = 0;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));
		m_CurrentTime = currentTime;

		m_DeltaTime = (m_CurrentTime - m_PrevTime) * m_SecondsPerCount;
		m_PrevTime = m_CurrentTime;

		if(m_DeltaTime < 0.0) {
			m_DeltaTime = 0.0;
		}
	}
	
}

#endif
