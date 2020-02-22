#include <iostream>
#include <fstream>
#include <majorities.h>
#include <bitmap.h>
#include <random>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;

std::random_device rd;
std::mt19937 rng {rd()};

std::vector<int> randomVector(int n) {
    std::uniform_int_distribution<int> elementDist(1, 10);
    std::vector<int> answer(n);
    for(auto& el : answer) {
        el = elementDist(rng);
    }  
    return answer;
}

int millisDif(Clock::time_point t1, Clock::time_point t2) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 -t1).count();   
}

void constructionExperiment() {
    std::ofstream constructionTimes("constructionTimes.txt");
    // Construction times, tau = 0.5 constant
    std::vector<int> cTimes;
    for(int n = 100; n < 5000; n += 10) {
        std::vector<int> v = randomVector(n);
        if(n % 100 == 0) std::cout << "n = " << n << std::endl;
        auto t1 = Clock::now();
        Maj<int, Bitmap> maj(v, 0.5);
        auto t2 = Clock::now();
        int millis = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cTimes.push_back(millis);
    }

    for(const auto& time: cTimes) {
        constructionTimes << time << std::endl;
    } 
}

void queriesExperiment(int maxSize, int experimentSize, int nQueries) {
    std::ofstream queryTimes("queryTimes.txt");

    std::vector<int> qTimes;
    int totalResult = 0;
    for(int i = 0; i < experimentSize; ++i) {    
        std::vector<int> v = randomVector((i+1)* (maxSize / experimentSize));
        Maj<int, Bitmap> maj(v, 0.1);
        std::uniform_int_distribution<int> queryDist(0, int(v.size())-1);
        auto t1 = Clock::now();
        for(int q = 0; q < nQueries; ++q) {
            int a = queryDist(rng);
            int b = queryDist(rng);
            if(a > b) std::swap(a,b);
            if(a == b) {if(a) {a--;} else { b++;}}
            totalResult += maj.findFirstMajority(a, b, 0.1);
        }
        auto t2 = Clock::now();
        qTimes.push_back(millisDif(t1, t2));
    }
    for(const auto& time: qTimes) {
        queryTimes << time << std::endl;
    }   
    std::cout << totalResult << std::endl;
}

void tauExperiment(int size,int nExperiments, int nQueries) {
    std::ofstream tauTimes("tauTimes.txt");

    std::vector<int> tTimes;
    int totalResult = 0;
    for(int i = 0; i < nExperiments; ++i) {    
        std::vector<int> v = randomVector(size);
        float tau = (i+1) * 1.0 / nExperiments;
        Maj<int, Bitmap> maj(v, tau);
        std::uniform_int_distribution<int> queryDist(0, int(v.size())-1);
        auto t1 = Clock::now();
        for(int q = 0; q < nQueries; ++q) {
            int a = queryDist(rng);
            int b = queryDist(rng);
            if(a > b) std::swap(a,b);
            if(a == b) {if(a) {a--;} else { b++;}}
            totalResult += maj.findFirstMajority(a, b, tau);
        }
        auto t2 = Clock::now();
        tTimes.push_back(millisDif(t1, t2));
    }
    for(const auto& time: tTimes) {
        tauTimes << time << std::endl;
    }   
  
    std::cout << totalResult << std::endl;
}

void memoryExperiment(int nExperiments, int maxSize) {
    std::ofstream memFile("memory.txt");

    std::vector<int> mems;
    int totalResult = 0;
    for(int i = 0; i < nExperiments; ++i) {
        int size = ((i + 1) * maxSize) / nExperiments;
        std::vector<int> v = randomVector(size);
        float tau = 0.5;
        Maj<int, Bitmap> maj(v, tau);
        mems.push_back(maj.memory());
        totalResult += maj.findFirstMajority(0, size/2, tau);
        std::cout << "i = " << i << std::endl;
    }

    for(const auto& mem: mems) {
        memFile << mem << std::endl;
    }
    
    std::cout << totalResult << std::endl;

}

int main(int argc, char** argv) {
    int n = std::stoi(argv[1]);
    int m = std::stoi(argv[2]);
    //queriesExperiment(5000, 500, 1000000);
    memoryExperiment(n, m);
    return 0;
}
