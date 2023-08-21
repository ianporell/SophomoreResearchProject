#include "GenPass.h"
#include <time.h>
#include <random>

void GenPass::seed() {
    srand(time(0));
}

std::vector<std::string> GenPass::gen_passes(uint16_t n, uint8_t l, GenPass::charset charset) {
    std::vector<std::string> passes(n);
    for (uint16_t i = 0; i < n; i++) passes[i] = gen_pass(l, charset);
    return passes;
}

std::string GenPass::gen_pass(uint8_t n, GenPass::charset charset) {
    std::string password;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, charset.length() - 1);

    for (uint16_t i = 0; i < n; ++i) {
        char randomChar = charset[dist(gen)];
        password.push_back(randomChar);
    }

    return password;
}