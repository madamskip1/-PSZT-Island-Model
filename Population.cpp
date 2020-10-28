#include "Population.h"
#include "RandomNumber.h"

Population::Population(int size, int individualNeedToCross, int mutateChance, double boundary)
	: populationSize(size), individualNeedToCross(individualNeedToCross), mutateChance(mutateChance), boundary(boundary)
{
	Individual::boundary = boundary;
	generatePopulation();
}

void Population::crossoverAll()
{
	int newIndividuals = individuals.size() / individualNeedToCross;
	
	double newValue;
	std::shared_ptr<Individual> individualToAdd;
	std::vector<double> values;

	for (int i = 0; i < newIndividuals; i++)
	{
		newValue = 0;
		std::shared_ptr<Individual> child;
		
		for (int j = 1; j <= dimensions; j++)
		{
			newValue = 0;

			for (int k = 0; k < individualNeedToCross; k++)
			{
				newValue += individuals[i * individualNeedToCross + k]->getValue(j);
			}

			newValue /= individualNeedToCross;
			values.push_back(newValue);
		}

		newValue /= individualNeedToCross;

		individuals.push_back(std::make_shared<Individual>(values));
	}
}


void Population::killChilds()
{
	individuals.resize(populationSize);
}

void Population::tryMutateAll()
{
	RandomNumber* numberGenerator = RandomNumber::getInstance();

	int numberOfIndividuals = individuals.size();
	double standardDeviation = calculateDeviation();
	int negation = 1;
	int number;

	for (int i = 0; i < numberOfIndividuals; i++)
	{
		number = numberGenerator->randomInt(0, 100);
		if (number < mutateChance)
		{
			if (numberGenerator->randomInt(0, 1) == 1)
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
		avarage += individuals[i]->avgOfValues();

	avarage /= numberOfIndividuals;

	for (int i = 0; i < numberOfIndividuals; i++)
	{
		sqrtOfItem = individuals[i]->avgOfValues() - avarage;
		variance = +sqrtOfItem * sqrtOfItem;
	}

	variance /= numberOfIndividuals;

	double result = sqrt(variance);

	return result;
}

void Population::generatePopulation()
{
	RandomNumber* randomNumber = RandomNumber::getInstance();
	std::vector<double> values;

	for (int i = 0; i < dimensions; i++)
		values.push_back(randomNumber->randomDouble(-boundary, boundary));

	std::shared_ptr<Individual> newIndividual = std::make_shared<Individual>(values);

	individuals.push_back(newIndividual);
}

