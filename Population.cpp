#include "Population.h"
#include <algorithm>
#include <iostream>

Population::Population(int size, int mutateChance, double boundary, int dimensions)
	: populationSize(size), mutateChance(mutateChance), boundary(boundary), dimensions(dimensions)
{
	Individual::boundary = boundary;
	randomNumber = RandomNumber::getInstance();
	generatePopulation();
}

Population::~Population()
{
}

void Population::crossoverAll()
{
	for (int i = 0; i < populationSize * crossoverPercentage/200; i = i + 2)
	{
		individuals.push_back(crossover(individuals[i], individuals[i + 1]));
		individuals.push_back(crossover(individuals[i], individuals[i + 1]));

	}
	for (int i = 0; i < populationSize * crossoverPercentage/200; i = i + 2)
	{
		int a = randomNumber->randomInt(0, populationSize);
		int b = randomNumber->randomInt(populationSize/2, populationSize);
		individuals.push_back(crossover(individuals[a], individuals[b]));
		individuals.push_back(crossover(individuals[a], individuals[b]));
	}
}

std::shared_ptr<Individual> Population::crossover(const std::shared_ptr<Individual>& parent1, const std::shared_ptr<Individual>& parent2)
{
	double weight = randomNumber->randomDouble(0, 1);
	std::vector<double> values;
	double val;
	int half = weight * dimensions;

	for (int i = 0; i < half; ++i)
	{
		values.push_back(parent1->getValue(i));
	}
	for (int i = half; i < dimensions; ++i)
	{
		values.push_back(parent2->getValue(i));
	}


	return std::make_shared<Individual>(values);
}


void Population::killChildren()
{
	individuals.erase(individuals.begin(), individuals.end() - 100);
}

void Population::tryMutateAll()
{
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<double> normal(0.0, 1);
	double mutateOp = 0.1 * normal(gen);

	int numberOfIndividuals = individuals.size();
	int number;
	int position;

	for (int i = 0; i < numberOfIndividuals; ++i)
	{
		for (int j = 0; j < dimensions; ++j)
	{
		number = randomNumber->randomInt(0, 1000);
		position = randomNumber->randomInt(0, dimensions);
		if (number <= mutateChance)
		{
			individuals[i]->mutate(mutateOp, j);
		}
	}
}}

double Population::getBestFitness()
{
	return individuals[0]->getFitness();
}

double Population::getWorstFitness()
{
	return individuals[populationSize-1]->getFitness();
}

void Population::generatePopulation()
{
	for (int i = 0; i < populationSize; i++)
		individuals.push_back(generateIndividual());
}

std::shared_ptr<Individual> Population::generateIndividual()
{
	std::vector<double> values;
	for (int i = 0; i < dimensions; i++)
		values.push_back(randomNumber->randomDouble(-boundary, boundary));

	return std::make_shared<Individual>(values);
}

void Population::sortIndividuals()
{
	std::sort(individuals.begin(), individuals.end(), [](const std::shared_ptr<Individual> first, const std::shared_ptr<Individual> second)
		{
			return first->getFitness() < second->getFitness();
		});
}

void Population::leaveBest()
{
	for (int i = 0; i < populationSize * bestPercentage/100; ++i)
	{
		individuals.push_back(std::make_shared<Individual>(individuals[i]->getValues()));
	}
}

void Population::migration(std::shared_ptr<Population> other)
{
	int migration = randomNumber->randomInt(0, migrationSize);
	int a;
	int b;
	for(int i=0; i<migration; ++i)
	{
		a = randomNumber->randomInt(0, populationSize-1);
		b = randomNumber->randomInt(0, (bestPercentage*populationSize/100)-1);
		individuals[a]->setValues(other->getIndividual(b)->getValues());
	}
}

std::shared_ptr<Individual> Population::getIndividual(int position)
{
	return individuals[position];
}

