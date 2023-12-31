#pragma once
#include "Saturn/Core/Core.h"
#include "Saturn/IO/Log.h"

#include <stdexcept>
#include <optional>
#include <vector>

namespace Saturn::IO
{
	class File
	{
	public:
		static bool Exists(const std::string& path);
		static std::string ReadAllText(const std::string& path);
		static std::vector<std::string> ReadAllLines(const std::string& path);
	};
}