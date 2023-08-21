#include <iostream>
#include <fstream>
#include "GenPass.h"
#include "Hash.h"
#include "Crack.h"

#define SAMPLE_SIZE 100
#define CHARSET alpha

void runTest(uint16_t sampleSize, uint8_t passLength, GenPass::charset charset) {
    GenPass::seed();
    std::vector<std::string> passes = GenPass::gen_passes(sampleSize, passLength, charset);

    std::ofstream output("output.txt");
    output << "TEST: SAMPLE SIZE: " << sampleSize << ", PASS LENGTH: " << passLength << ", CHARSET: " << charset << std::endl;
    uint64_t total = 0;
    for (std::string pass : passes) {
        uint64_t time = Crack::crack(Hash::generateSHA256Hash(pass), charset);
        total += time;
        output << time << " ";
        std::cout << "Ms: " << time << std::endl;
    }
    output << std::endl << "AVERAGE: " << total / sampleSize;
    output.close();
}

int main()
{
    GenPass::charset alpha = "abcdefghijklmnopqrstuvwxyz";
    GenPass::charset uppercaseAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    GenPass::charset numbers = "1234567890";
    GenPass::charset symbols = ":;*&^%$#@!";
    GenPass::charset maxComplexity = alpha + uppercaseAlpha + numbers + symbols;
    
    runTest(SAMPLE_SIZE, 2, CHARSET);
}

