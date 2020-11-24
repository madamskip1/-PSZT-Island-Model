#pragma once
#include <vector>
#include <memory>
#include "Individual.h"
#include "RandomNumber.h"

class Population
{	
	std::vector<std::shared_ptr<Individual>> individuals;
	int populationSize{0};
	int mutateChance{0};
	int dimensions{0};
	double boundary{0};

	static int crossoverPercentage;
	static int bestPercentage;
	static int migrationSize;
	static double sigma;
	RandomNumber* randomNumber{nullptr};

public:
	Population(int size, int mutateChance, double boundary, int dimensions);
	~Population();
	void crossoverAll();
	void killPredecessors();
	void tryMutateAll();
	void migration(std::shared_ptr<Population> other);
	void sortIndividuals();
	void leaveBest();
	double getBestFitness();
	double getWorstFitness();

private:
	void generatePopulation();
	std::shared_ptr<Individual> crossover(const std::shared_ptr<Individual>& parent1, const std::shared_ptr<Individual>& parent2);
	std::shared_ptr<Individual> generateIndividual();
	std::shared_ptr<Individual> getIndividual(int position);
};




