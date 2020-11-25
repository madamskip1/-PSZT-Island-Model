#include "Population.h"
#include "ConfigInterpreter.h"
#include <algorithm>
#include <iostream>

int Population::crossoverPercentage{0};
int Population::bestPercentage{0};
int Population::migrationSize{0};
double Population::sigma{0};

Population::Population(int size, int mutateChance, double boundary, int dimensions)
	: populationSize(size), mutateChance(mutateChance), boundary(boundary), dimensions(dimensions)
{
	if(bestPercentage == 0 && crossoverPercentage == 0)
	{
		ConfigInterpreter* config = ConfigInterpreter::getInstance("config.txt");
		crossoverPercentage = config->getConfigValue(ConfigInterpreter::CROSSOVER);
		bestPercentage = config->getConfigValue(ConfigInterpreter::BEST);
		migrationSize = config->getConfigValue(ConfigInterpreter::MIGRATION);
		sigma = static_cast<double>(config->getConfigValue(ConfigInterpreter::SIGMA))/10;
	}
	Individual::boundary = boundary;
	randomNumber = RandomNumber::getInstance();
	generatePopulation();
}

Population::~Population()
{
}

void Population::crossoverAll()
{
	int bestParents = populationSize*bestPercentage/100;
	int prefferedParents = populationSize*bestPercentage*4/100;
	int quarterOfCrossoveredPopulation = populationSize * crossoverPercentage/400; 

	for (int i = 0; i <= quarterOfCrossoveredPopulation+1; ++i)
	{
		int a = i;
		int b = randomNumber->randomInt(0, bestParents);
		individuals.push_back(crossover(individuals[a], individuals[b]));
	}

	for (int i = 0; i <= quarterOfCrossoveredPopulation*3; ++i)
	{
		int a = randomNumber->randomInt(0, populationSize);
		int b = randomNumber->randomInt(populationSize/2, populationSize-1);
		individuals.push_back(crossover(individuals[a], individuals[b]));
	}
}

std::shared_ptr<Individual> Population::crossover(const std::shared_ptr<Individual>& parent1, const std::shared_ptr<Individual>& parent2)
{
	std::vector<double> values;

	for (int i = 0; i < dimensions; ++i)
	{
		int parentGene = randomNumber->randomInt(0, 1);
		if (parentGene == 0)
			values.push_back(parent1->getValue(i));
		
		else
			values.push_back(parent2->getValue(i));
	}

	return std::make_shared<Individual>(values);
}


void Population::killPredecessors()
{
	individuals.erase(individuals.begin(), individuals.begin() + populationSize);
	individuals.resize(populationSize);
}

void Population::tryMutateAll()
{
	static double max;
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<double> normal(0.0, sigma);
	int numberOfIndividuals = individuals.size();
	int number;
	int position;

	for (int i = 0; i < numberOfIndividuals; ++i)
	{
		for (int j = 0; j < dimensions; ++j)
		{
			number = randomNumber->randomInt(0, 1000);
			position = randomNumber->randomInt(0, dimensions);
			if (number < mutateChance)
			{
				individuals[i]->mutate(normal(gen), j);
			}
		}
	}
}

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
	int leave = populationSize * bestPercentage/100;
	for (int i = 0; i < leave; ++i)
	{
		individuals.push_back(std::make_shared<Individual>(individuals[i]->getValues()));
	}
}

void Population::migration(std::shared_ptr<Population> other)
{
	int migrationCount = populationSize*migrationSize/1000;
	int migration = randomNumber->randomInt(0, migrationCount);
	int a;
	int b;
	for(int i=0; i < migration; ++i)
	{
		a = randomNumber->randomInt(0, populationSize-1);
		b = randomNumber->randomInt(bestPercentage*populationSize/100, populationSize-1);
		individuals[a]->setValues(other->getIndividual(b)->getValues());
	}
}

std::shared_ptr<Individual> Population::getIndividual(int position)
{
	return individuals[position];
}

