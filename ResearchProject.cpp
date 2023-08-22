#include <iostream>
#include <fstream>
#include <thread>
#include <sstream>
#include <atomic>
#include "GenPass.h"
#include "Hash.h"
#include "Crack.h"

#define NUM_THREADS 8
#define SAMPLE_SIZE 1000

GenPass::charset alpha = "abcdefghijklmnopqrstuvwxyz";
GenPass::charset uppercaseAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
GenPass::charset numbers = "1234567890";
GenPass::charset symbols = ":;*&^%$#@!";

void threadWorker(const std::vector<std::string>& passes, std::ofstream& outputFile, std::atomic<uint64_t>& total, GenPass::charset charset) {
    uint64_t localTotal = 0;
    std::string outputStr;
    std::ostringstream output;

    for (const std::string& pass : passes) {
        uint64_t time = Crack::crack(Hash::generateSHA256Hash(pass), charset);
        output << time << " ";
        localTotal += time;
    }

    total += localTotal;

    outputFile << output.str();
    outputFile.flush();
}

void runTest(uint16_t sampleSize, uint8_t passLength, GenPass::charset charset) {
    GenPass::seed();
    std::vector<std::string> passes = GenPass::gen_passes(sampleSize, passLength, charset);

    std::ofstream output("output.txt", std::ios::app);
    output << std::endl << "TEST: SAMPLE SIZE: " << sampleSize << ", PASS LENGTH: " << static_cast<int>(passLength) << ", CHARSET: " << charset << std::endl;
    std::atomic<uint64_t> total = 0;
    std::vector<std::thread> threads;

    for (uint8_t i = 0; i < NUM_THREADS; i++) {
        int startIndex = i * (sampleSize / NUM_THREADS);
        int endIndex = (i == NUM_THREADS - 1) ? sampleSize : (i + 1) * (sampleSize / NUM_THREADS);
        if (i == NUM_THREADS) {
            endIndex = sampleSize;
        }

        threads.emplace_back(std::thread(threadWorker, std::vector<std::string>(passes.begin() + startIndex, passes.begin() + endIndex), std::ref(output), std::ref(total), charset));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    output << std::endl << "AVERAGE: " << static_cast<double>(total) / sampleSize << ", TOTAL: " << total;
    output.close();
}

void prompt() {
    while (true) {
        std::cout << "Input charset" << std::endl;
        std::string charsetSelection;
        std::cin >> charsetSelection;

        std::cout << "Input sample size" << std::endl;
        int sampleSizeSelection;
        std::cin >> sampleSizeSelection;

        std::cout << "Input pass length" << std::endl;
        int passLengthSelection;
        std::cin >> passLengthSelection;

        if (charsetSelection == "alpha") {
            runTest(sampleSizeSelection, passLengthSelection, alpha);
        }
        else if (charsetSelection == "maxComplexity") {
            runTest(sampleSizeSelection, passLengthSelection, alpha + uppercaseAlpha + numbers + symbols);
        }
    }
}

void runRelevantTests() {
    runTest(SAMPLE_SIZE, 1, alpha);
    std::cout << "Test 1 completed" << std::endl;
    runTest(SAMPLE_SIZE, 2, alpha);
    std::cout << "Test 2 completed" << std::endl;
    runTest(SAMPLE_SIZE, 3, alpha);
    std::cout << "Test 3 completed" << std::endl;
    runTest(SAMPLE_SIZE, 4, alpha);
    std::cout << "Test 4 completed" << std::endl;
    runTest(SAMPLE_SIZE, 5, alpha);
    std::cout << "Test 5 completed" << std::endl;

    runTest(SAMPLE_SIZE, 1, alpha + uppercaseAlpha);
    std::cout << "Test 6 completed" << std::endl;
    runTest(SAMPLE_SIZE, 2, alpha + uppercaseAlpha);
    std::cout << "Test 7 completed" << std::endl;
    runTest(SAMPLE_SIZE, 3, alpha + uppercaseAlpha);
    std::cout << "Test 8 completed" << std::endl;
    runTest(SAMPLE_SIZE, 4, alpha + uppercaseAlpha);
    std::cout << "Test 9 completed" << std::endl;
    runTest(SAMPLE_SIZE, 5, alpha + uppercaseAlpha);
    std::cout << "Test 10 completed" << std::endl;

    runTest(SAMPLE_SIZE, 1, alpha + uppercaseAlpha + numbers);
    std::cout << "Test 11 completed" << std::endl;
    runTest(SAMPLE_SIZE, 2, alpha + uppercaseAlpha + numbers);
    std::cout << "Test 12 completed" << std::endl;
    runTest(SAMPLE_SIZE, 3, alpha + uppercaseAlpha + numbers);
    std::cout << "Test 13 completed" << std::endl;
    runTest(SAMPLE_SIZE, 4, alpha + uppercaseAlpha + numbers);
    std::cout << "Test 14 completed" << std::endl;
    runTest(SAMPLE_SIZE, 5, alpha + uppercaseAlpha + numbers);
    std::cout << "Test 15 completed" << std::endl;

    runTest(SAMPLE_SIZE, 1, alpha + uppercaseAlpha + numbers + symbols);
    std::cout << "Test 16 completed" << std::endl;
    runTest(SAMPLE_SIZE, 2, alpha + uppercaseAlpha + numbers + symbols);
    std::cout << "Test 17 completed" << std::endl;
    runTest(SAMPLE_SIZE, 3, alpha + uppercaseAlpha + numbers + symbols);
    std::cout << "Test 18 completed" << std::endl;
    runTest(SAMPLE_SIZE, 4, alpha + uppercaseAlpha + numbers + symbols);
    std::cout << "Test 19 completed" << std::endl;
    runTest(SAMPLE_SIZE, 5, alpha + uppercaseAlpha + numbers + symbols);
    std::cout << "Test 20 completed" << std::endl;
}

int main()
{
    std::cout << "a: run any test" << std::endl << "b: run all relevant tests back-to-back" << std::endl;
    char result;
    std::cin >> result;

    switch (result) {
        case 'a':
            prompt();
            break;
        case 'b':
            runRelevantTests();
            break;
    }
}

