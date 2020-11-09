#pragma once
#include <vector>
#include <memory>
#include "Individual.h"
#include "RandomNumber.h"

class Population
{
	static constexpr int crossoverPercentage{96};
	static constexpr int bestPercentage{4};
	static constexpr int migrationSize{1};
	
	
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
	void killChildren();
	void tryMutateAll();
	double getBestFitness();
	double getWorstFitness();
	void migration(std::shared_ptr<Population> other);
	void sortIndividuals();
	void leaveBest();
private:

	void generatePopulation();
	std::shared_ptr<Individual> crossover(const std::shared_ptr<Individual>& parent1, const std::shared_ptr<Individual>& parent2);
	std::shared_ptr<Individual> generateIndividual();
	std::shared_ptr<Individual> getIndividual(int position);
};

