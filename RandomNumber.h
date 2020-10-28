#pragma once
#include <random>

class RandomNumber
{
private:
	static RandomNumber* _instance;
	RandomNumber();

public:
	RandomNumber(RandomNumber& clone) = delete;
	static RandomNumber *getInstance();

	std::random_device randomDevice;
	std::mt19937_64 mt;

	int randomInt(int min, int max);
	double randomDouble(double min, double max);
};

