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
	crossoveredPos = individuals.size();
	for (int i = 0; i < populationSize * crossoverPercentage/2/100; i = i + 2)
	{
		individuals.push_back(crossover(individuals[i], individuals[i + 1]));
	}
	for (int i = 0; i < populationSize * crossoverPercentage/2/100; i = i + 2)
	{
		int a = randomNumber->randomInt(0, populationSize);
		int b = randomNumber->randomInt(0, populationSize);
		individuals.push_back(crossover(individuals[a], individuals[b]));
	}
	crossoveredCount = individuals.size() - crossoveredPos;
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


void Population::killChilds()
{

	std::vector<std::shared_ptr<Individual>> indivs;
	indivs.insert(indivs.end(), std::make_move_iterator(individuals.begin() + populationSize), std::make_move_iterator(individuals.end()));
	individuals = std::move(indivs);
}

void Population::show(int a)
{
	for(auto p : individuals[a].get()->getValues())
		std::cout<<p<<" ";
}


void Population::tryMutateAll()
{

	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<double> normal(0, 1);
	double mutateOp = 0.01 * normal(gen);

	int numberOfIndividuals = individuals.size();
	uint diff = individuals.size();
	for (int i=crossoveredPos; i<crossoveredPos+crossoveredCount; ++i)
	{
		individuals.push_back(individuals[i]->mutate(mutateOp));
	}
	diff = individuals.size() - diff;
	for (int i=bestCount+crossoveredCount + diff; i< populationSize; ++i)
	{
		individuals.push_back(individuals[i]->mutate(mutateOp));
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


		puts("\n\n\n\n");
	for(auto aa : individuals)
		printf("%f ", aa.get()->getFitness());
}

void Population::leaveBest()
{
	bestPos = individuals.size();
	for (int i = 0; i < populationSize * bestPercentage/100; ++i)
	{
		individuals.push_back(std::make_shared<Individual>(individuals[i].get()->getValues()));
	}
	bestCount = individuals.size() - bestPos;
}

