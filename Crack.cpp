#include "Crack.h"
#include "Hash.h"
#include "GenPass.h"
#include <string>
#include <chrono>


uint64_t Crack::crack(std::string hashed, GenPass::charset charset) {
    auto startTime = std::chrono::high_resolution_clock::now();
    int charsetSize = charset.length();

    for (int length = 1; length < 10; ++length) {
        std::string combination(length, charset[0]);

        while (true) {
            if (Hash::generateSHA256Hash(combination) == hashed) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = endTime - startTime;
                return static_cast<uint64_t>(duration.count() * 1000);
            }

            int position = length - 1;
            while (position >= 0 && combination[position] == charset[charsetSize - 1]) {
                combination[position] = charset[0];
                --position;
            }

            if (position < 0) {
                break;
            }

            combination[position] = charset[charset.find(combination[position]) + 1];
        }
    }

    return 0;
}