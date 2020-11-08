#pragma once
#include <random>

class RandomNumber
{
private:
	static RandomNumber* _instance;
	std::random_device randomDevice;
	std::mt19937_64 mt;
	RandomNumber();

public:
	RandomNumber(RandomNumber& clone) = delete;
	static RandomNumber *getInstance();
	virtual ~RandomNumber();

	int randomInt(int min, int max);
	double randomDouble(double min, double max);
};

