#include "JsonFileSerializer.h"

#include <fstream>

namespace pawn::engine {

	void JsonFileSerializer::SaveToFile(const std::string& path, const nlohmann::json& json) {
		std::ofstream outputFile;

		outputFile.open(path, std::fstream::out | std::ofstream::trunc | std::ofstream::binary);
		if (!outputFile.is_open()) {
			return;
		}

		outputFile << json.dump() << std::endl;
		outputFile.close();
	}

	nlohmann::json JsonFileSerializer::LoadFromFile(const std::string& path) {
		std::ifstream inputFile;

		inputFile.open(path, std::fstream::in | std::fstream::binary);
		if (!inputFile.is_open()) {
			return nlohmann::json();
		}

		std::string tempJsonData;
		inputFile >> tempJsonData;

		return nlohmann::json::parse(tempJsonData);
	}

}
