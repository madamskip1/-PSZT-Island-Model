#include "Population.h"
#include <cstdlib>
#include <ctime>

void Population::crossoverAll()
{
	int newIndividuals = individuals.size() / individualNeedToCross;
	
	int newValue;
	std::shared_ptr<Individual> individualToAdd;
	for (int i = 0; i < newIndividuals; i++)
	{
		newValue = 0;
		std::shared_ptr<Individual> child;

		for (int j = 0; j < individualNeedToCross; j++)
		{
			individualToAdd = individuals[i * individualNeedToCross + j];
			newValue += individualToAdd->getValue();
		}

		newValue /= individualNeedToCross;

		individuals.push_back(std::make_shared<Individual>(newValue));
	}
}


void Population::killChilds()
{
	individuals.resize(maxNumberOfIndividual);
}

void Population::tryMutateAll()
{
	int numberOfIndividuals = individuals.size();
	int number;
	srand((unsigned)time(0));

	for (int i = 0; i < numberOfIndividuals; i++)
	{
		number = (rand() % 100);
		if (number < mutateChance)
			mutate(individuals[i]);
	}
}

void Population::mutate(std::shared_ptr<Individual> individual)
{
	// Todo: mutate individual
	// or move it to Individual class - probably better
}

