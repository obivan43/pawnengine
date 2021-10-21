#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class TransformationComponentScriptRegister final : public RegisterScriptClass {

		public:
			TransformationComponentScriptRegister() = default;
			TransformationComponentScriptRegister(const TransformationComponentScriptRegister& other) = delete;
			TransformationComponentScriptRegister(TransformationComponentScriptRegister&& other) noexcept = delete;

			TransformationComponentScriptRegister& operator=(const TransformationComponentScriptRegister& other) = delete;
			TransformationComponentScriptRegister& operator=(TransformationComponentScriptRegister&& other) noexcept = delete;

			void Register(sol::state& lua) const override final;

	};

}
