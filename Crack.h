#pragma once

#include <string>
#include "GenPass.h"

class Crack
{
	public:
		static uint64_t crack(std::string hashed, GenPass::charset charset);
};

