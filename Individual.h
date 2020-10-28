#pragma once
class Individual
{
public:
	static double boundary;
private:
	double fitness;
	int value;
public:
	//Individual();
	Individual(int value);
	//virtual void calculateFitness();
	int getValue();
	void mutate(const double &standardDeviation);
};

