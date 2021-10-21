#pragma once

#include "JsonSerializer.h"

namespace pawn::engine {

	class JsonFileSerializer {

		public:
			JsonFileSerializer() = delete;
			JsonFileSerializer(const JsonSerializer& other) = delete;
			JsonFileSerializer(JsonSerializer&& other) noexcept = delete;

			JsonSerializer& operator=(const JsonSerializer& other) = delete;
			JsonSerializer& operator=(JsonSerializer&& other) noexcept = delete;

			static void SaveToFile(const std::string& path, const nlohmann::json& json);
			static nlohmann::json LoadFromFile(const std::string& path);
	};

}
