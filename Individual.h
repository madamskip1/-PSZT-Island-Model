#pragma once
#include <vector>
#include <memory>

class Individual
{
public:
	static double boundary;
	
	Individual(double value);
	Individual(std::vector<double> values);
	double getFitness();
	double getValue(int dimension);
	std::vector<double> getValues();
	void setValue(int dimension, double value);
	void setValues(std::vector<double> values);
	void mutate(const double & mutateOp, int position);
	void migrate(const Individual& other);

private:
	double fitness;
	std::vector<double> values;

	void calculateFitness();
	void rastrigin();
	void ackley();
};

