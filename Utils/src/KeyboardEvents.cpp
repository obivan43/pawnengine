#include "pch.h"
#include "KeyboardEvents.h"


namespace pawn {

	KeyboardPress::KeyboardPress(uint8_t code) : Event(EventTypeEnum::KeyboardPress), m_Code(code) {}

	KeyboardRelease::KeyboardRelease(uint8_t code) : Event(EventTypeEnum::KeyboardRelease), m_Code(code) {}

}