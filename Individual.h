#pragma once
#include <vector>

class Individual
{
public:
	static double boundary;
private:
	double fitness;
	std::vector<double> values;
public:
	Individual(int value);
	Individual(std::vector<int> values);
	void calculateFitness();
	double getValue(int dimension);
	std::vector<double> getValues();
	void mutate(const double &standardDeviation);
	double sumOfValues();
	double avgOfValues();

};

