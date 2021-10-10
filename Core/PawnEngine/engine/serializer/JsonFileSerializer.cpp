#include "JsonFileSerializer.h"

#include <fstream>

namespace pawn {

	namespace engine {

		void JsonFileSerializer::SaveToFile(const std::string& path, const json& j) {
			std::ofstream outputFile;

			outputFile.open(path, std::fstream::out | std::ofstream::trunc | std::ofstream::binary);
			if (!outputFile.is_open()) {
				return;
			}

			outputFile << j.dump() << std::endl;
			outputFile.close();
		}

		json JsonFileSerializer::LoadFromFile(const std::string& path) {
			std::ifstream inputFile;

			inputFile.open(path, std::fstream::in | std::fstream::binary);
			if (!inputFile.is_open()) {
				return json();
			}

			std::string tempJsonData;
			inputFile >> tempJsonData;

			return json::parse(tempJsonData);
		}

	}

}
