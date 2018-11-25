#include "Utils.h"



int Utils::random(int min, int max)
{
    std::random_device rd;
    static std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(eng);
}

int Utils::random(int max)
{
    random(0, max);
}