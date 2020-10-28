#pragma once
class Individual
{
private:
	double fitness;
	int value;
public:
	Individual(int value);
	virtual void calculateFitness();
	int getValue();
};

