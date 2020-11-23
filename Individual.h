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
	void setValues(std::vector<double> values);
	std::vector<double> getValues();
	void mutate(const double & mutateOp, int position);
	void migrate(const Individual& other);
private:
	void calculateFitness();
	void rastrigin();
	void ackley();
};

