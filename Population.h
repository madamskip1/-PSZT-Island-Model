#pragma once
#include <vector>
#include <memory>
#include "Individual.h"
#include "RandomNumber.h"
class Population
{
	std::vector<std::shared_ptr<Individual>> individuals;
	int populationSize;
	int mutateChance;
	int dimensions;
	double boundary;
	RandomNumber* randomNumber;
public:
	Population(int size, int mutateChance, double boundary, int dimensions);
	~Population();
	void crossoverAll();
	void killChilds();
	void tryMutateAll();
	double getBestFitness();
	void sortIndividuals();
private:
	void generatePopulation();
	std::shared_ptr<Individual> crossover(const std::shared_ptr<Individual>& parent1, const std::shared_ptr<Individual>& parent2);
	std::shared_ptr<Individual> generateIndividual();
};

