#pragma once

#define EVENT_INFO(type)	static EventTypeEnum StaticType() { return EventTypeEnum::##type; } \
							virtual const char* Name() const override { return #type; }

namespace pawn
{
	enum class EventTypeEnum {
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved
	};
	
	class Event {

		public:
			Event(EventTypeEnum type);
			Event(const Event& other) = default;
			Event(Event&& other) noexcept = default;
		
			Event& operator=(const Event& other) = default;
			Event& operator=(Event&& other) noexcept = default;
		
			virtual ~Event() = default;

			EventTypeEnum GetType() const { return m_Type; }
			bool GetIsHandeled() const { return m_IsHandeled; }

			void SetHandeled(bool state) { m_IsHandeled = state; }
		
			virtual const char* Name() const = 0;

		private:
			EventTypeEnum m_Type;
			bool m_IsHandeled;
	};
}

