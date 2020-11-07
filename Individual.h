#pragma once
#include <vector>
#include <memory>

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
	double getFitness();
	double getValue(int dimension);
	void setValue(int dimension, double value);
	std::vector<double> getValues();
	std::shared_ptr<Individual> mutate(const double & mutateOp);
private:
	void calculateFitness();
};

