#pragma once
#include <vector>
#include <memory>
#include "Individual.h"
class Population
{
	std::vector<std::shared_ptr<Individual>> individuals;
	int maxNumberOfIndividual;
	int individualNeedToCross;
	int mutateChance;
public:
	void crossoverAll();
	void killChilds();
	void tryMutateAll();
private:
	void crossover(const std::vector<std::shared_ptr<Individual>> &individuals);
	void mutate(std::shared_ptr<Individual> individual);
};

