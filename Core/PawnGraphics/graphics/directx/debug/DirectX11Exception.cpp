#include "DirectX11Exception.h"

#include <sstream>
#include <iomanip>

namespace pawn::graphics {

	DirectX11Exception::DirectX11Exception(
		HRESULT result,
		const char* file,
		unsigned int line,
		const char* expression,
		const std::vector<std::string>& messages
	) : m_Result(result)
		, m_Line(line)
		, m_File(file)
		, m_Expression(expression) {

		for (const auto& m : messages) {
			m_Info += m;
			m_Info.push_back('\n');
		}

		if (!m_Info.empty()) {
			m_Info.pop_back();
		}

	}

	const char* DirectX11Exception::what() const noexcept {
		std::ostringstream oss;

		oss << "DirectX11 Exception" << std::endl << std::endl;
		oss << "[Error Info] : " << m_Info << std::endl << std::endl;
		oss << "[Error Code] : " << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_Result << std::endl << std::endl;
		oss << "[Error Line] : " << m_Line << std::endl << std::endl;
		oss << "[Error File] : " << m_File << std::endl << std::endl;
		oss << "[Error Expression] : " << m_Expression << std::endl << std::endl;

		m_WhatCache = oss.str();
		return m_WhatCache.c_str();
	}


}