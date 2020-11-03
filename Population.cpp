#include <algorithm>
#include "Population.h"

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
	delete randomNumber;
}
void Population::crossoverAll()
{
	for (int i = 0; i < populationSize; i = i + 2)
	{
		individuals.push_back(crossover(individuals[i], individuals[i + 1]));
	}
}

std::shared_ptr<Individual> Population::crossover(const std::shared_ptr<Individual>& parent1, const std::shared_ptr<Individual>& parent2)
{
	double weight = randomNumber->randomDouble(0, 1);
	std::vector<double> values;
	double val;
	for (int i = 1; i <= dimensions; i++)
	{
		val = parent1->getValue(i) * weight + parent2->getValue(i) * (1 - weight);
		values.push_back(val);
	}

	return std::make_shared<Individual>(values);
}


void Population::killChilds()
{
	individuals.resize(populationSize);
}

void Population::tryMutateAll()
{

	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<double> normal(0.0, 1);
	double mutateOp = 0.1 * normal(gen);

	int numberOfIndividuals = individuals.size();
	int number;

	for (int i = 0; i < numberOfIndividuals; i++)
	{
		number = randomNumber->randomInt(0, 1000);
		if (number <= mutateChance)
		{
			individuals[i]->mutate(mutateOp);
		}
	}
}

double Population::getBestFitness()
{
	return individuals[0]->getFitness();
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

