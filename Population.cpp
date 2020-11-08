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
	for (int i=0; i<weight*dimensions;++i)
	{
		values.push_back(parent1->getValue(i));
	}
	for (int i=weight*dimensions; i<dimensions;++i)
	{
		values.push_back(parent2->getValue(i));
	}


	return std::make_shared<Individual>(values);
}


void Population::killChildren()
{

	std::vector<std::shared_ptr<Individual>> indivs;
	indivs.insert(indivs.end(), std::make_move_iterator(individuals.end() - populationSize), std::make_move_iterator(individuals.end()));
	individuals = std::move(indivs);
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
		individuals.push_back(std::make_shared<Individual>(individuals[i].get()->getValues()));
	}
}

void Population::migration(Population& other)
{
	int migration = randomNumber->randomInt(0, migrationSize);
	int a;
	int b;
	for(int i=0; i<migration; ++i)
	{
		a = randomNumber->randomInt(0, populationSize-1);
		b = randomNumber->randomInt(0, (bestPercentage*populationSize/100)-1);
		individuals[a]->migrate(*other.getIndividual(b).get());
	}
}

std::shared_ptr<Individual> Population::getIndividual(uint position)
{
	return individuals[position];
}

