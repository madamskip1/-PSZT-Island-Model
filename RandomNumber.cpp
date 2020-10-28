#include "RandomNumber.h"
#include <cstdlib>
#include <ctime>
#include <random>

RandomNumber * RandomNumber::_instance = nullptr;

RandomNumber* RandomNumber::getInstance()
{
    if (_instance == nullptr)
        _instance = new RandomNumber();

    return _instance;
}

RandomNumber::RandomNumber()
{
    mt = std::mt19937_64(randomDevice());

}

int RandomNumber::randomInt(int min, int max)
{
    //return (rand() % max) + min;
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(mt);
}

double RandomNumber::randomDouble(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(mt);
}