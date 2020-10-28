#pragma once
#include <vector>
#include <memory>
#include "Individual.h"
class Population
{
	std::vector<std::shared_ptr<Individual>> individuals;
	int populationSize;
	int individualNeedToCross;
	int mutateChance;
	double boundary;
public:
	Population(int size, int individualNeedToCross, int mutateChance, double boundary);

	void crossoverAll();
	void killChilds();
	void tryMutateAll();
private:
	//void crossover(const std::vector<std::shared_ptr<Individual>> &individuals);
	double calculateDeviation();
	void generatePopulation();
};

