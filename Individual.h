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
	Individual(double value);
	Individual(std::vector<double> values);
	void calculateFitness();
	double getFitness();
	double getValue(int dimension);
	std::vector<double> getValues();
	void mutate(const double &standardDeviation);
	double sumOfValues();
	double avgOfValues();

};

