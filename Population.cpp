#include "Population.h"
#include <cstdlib>
#include <ctime>

Population::Population(int size, int individualNeedToCross, int mutateChance, double boundary)
	: populationSize(size), individualNeedToCross(individualNeedToCross), mutateChance(mutateChance), boundary(boundary)
{
	Individual::boundary = boundary;
	generatePopulation();
}

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
	individuals.resize(populationSize);
}

void Population::tryMutateAll()
{
	int numberOfIndividuals = individuals.size();
	double standardDeviation = calculateDeviation();
	int negation = 1;
	int number;
	srand((unsigned)time(0));

	for (int i = 0; i < numberOfIndividuals; i++)
	{
		number = (rand() % 100);
		if (number < mutateChance)
		{
			if ((rand() % 1) == 1)
				negation *= -1;

			individuals[i]->mutate(negation * standardDeviation);
		}
	}
}

double Population::calculateDeviation()
{
	double variance = 0;
	double avarage = 0;
	double sqrtOfItem;
	int numberOfIndividuals = individuals.size();
	for (int i = 0; i < numberOfIndividuals; i++)
		avarage += individuals[i]->getValue();
	avarage /= numberOfIndividuals;

	for (int i = 0; i < numberOfIndividuals; i++)
	{
		sqrtOfItem = individuals[i]->getValue() - avarage;
		variance = +sqrtOfItem * sqrtOfItem;
	}

	variance /= numberOfIndividuals;

	double result = sqrt(variance);

	return result;
}

void Population::generatePopulation()
{
	
}

