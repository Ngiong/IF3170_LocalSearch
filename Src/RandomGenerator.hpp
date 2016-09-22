#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include <unistd.h>
#include <thread>
#include <chrono>
using namespace std;

class RandomGenerator
{

    public:
    	RandomGenerator();
        static RandomGenerator* getInstance() { return _instance; }

        int nextInt(int);
        int nextInt(int, int);
        double nextDouble();

    private:
        static RandomGenerator* _instance; 
};

RandomGenerator* RandomGenerator::_instance = new RandomGenerator;

RandomGenerator::RandomGenerator()
{
    struct timespec ts;
    clock_gettime (CLOCK_MONOTONIC, &ts);
    srand ((time_t)ts.tv_nsec);
}

int RandomGenerator::nextInt(int a)
{
    struct timespec ts;
    clock_gettime (CLOCK_MONOTONIC, &ts);
    srand ((time_t)ts.tv_nsec);
    int res = (rand() % a);
    return res;
}

int RandomGenerator::nextInt(int a, int b)
{
    struct timespec ts;
    clock_gettime (CLOCK_MONOTONIC, &ts);
    srand ((time_t)ts.tv_nsec);
    int intervalLength = b-a+1;
    int res = ((rand() % intervalLength) + a);
    return res;
}

double RandomGenerator::nextDouble()
{
    struct timespec ts;
    clock_gettime (CLOCK_MONOTONIC, &ts);
    srand ((time_t)ts.tv_nsec);
    return (rand() / (double) RAND_MAX);
}

# endif
