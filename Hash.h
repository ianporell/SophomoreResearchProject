#pragma once

#include <string>

class Hash
{
	public:
		static std::string generateSHA256Hash(const std::string& message);
};

