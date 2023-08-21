#pragma once

#include <string>
#include <vector>


class GenPass
{
	public:
		typedef const std::string& charset;

		static void seed();

		static std::vector<std::string> gen_passes(uint16_t n, uint8_t l, GenPass::charset charset);

		static std::string gen_pass(uint8_t n, GenPass::charset charset);
};

