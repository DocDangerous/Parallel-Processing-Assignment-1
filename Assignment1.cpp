#include <iostream>
#include <thread>
#include <queue>
#include <cmath>
#include <chrono>
#include <fstream>
#include <mutex>

std::mutex primeMutex;
std::mutex counterMutex;
int counter = 2;
int primeCount = 0;
long long primeSum = 0;
std::queue<int> topTen;

bool isPrime(int val) {
    int sqrt = static_cast<int>(std::sqrt(val));

    for (int k = 2; k <= sqrt; k++) {
        if (val % k == 0) {
            return false;
        }
    }

    return true;
}

// This is a scary function
void enqueueTopTen(int val) {
    if (!topTen.empty()) {
        if (topTen.back() >= val) {
            return;
        }
        if (topTen.size() >= 10) {
            topTen.pop();
        }
    }

    topTen.push(val);
    return;
}

void primePrint(int current) {
    std::lock_guard<std::mutex> lock(primeMutex);

    primeCount++;
    primeSum += current;
    enqueueTopTen(current);

    return;
}

void primeThread() {
    int current = 2;

    while(current < 100000000-8) { // Yeah that looks ugly but it also looks better
        {
            std::lock_guard<std::mutex> lock(counterMutex);
            current = counter++;
        }

        if (isPrime(current)) {
            primePrint(current);
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::thread threads[8];

    for (int i = 0; i < 8; i++) {
        threads[i] = std::thread(primeThread);
    }

    for (int i = 0; i < 8; i++) {
        threads[i].join();
    }

    if (topTen.size() != 10) {
        std::cout << "We got a problem here." << std::endl;
        return 0;
    }


    int finalTen[10];
    for (int t = 0; t < 10; t++) {
        finalTen[t] = topTen.front();
        topTen.pop();
    }

    std::ofstream outputFile("primes.txt");

    if (!outputFile.is_open()) {
        std::cout << "We got an output problem here." << std::endl;
        return 0;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto runtime = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    outputFile << "Execution time: " << runtime.count() << "milliseconds\n";
    outputFile << "Total number of primes found: " << primeCount << "\n";
    outputFile << "Sum of all primes found: " << primeSum << "\n";
    outputFile << "Top ten largest primes (from lowest to highest): ";
    for (int y = 0; y < 10; y++) {
        outputFile << finalTen[y] << " ";
    }
    outputFile.close();
    return 0;
}
