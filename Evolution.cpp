#include "Evolution.h"
#include "ConfigInterpreter.h"
#include <iostream>
#include <unistd.h>
Evolution::Evolution()
{
	config = new ConfigInterpreter("config.txt");
	maxGeneration = config->getConfigValue(ConfigInterpreter::GENERATIONS);
	generatePopulations();
	run();
}

Evolution::~Evolution()
{
	delete config;
}

void Evolution::run()
{
	int populationsSize = populations.size();
	populations[0]->sortIndividuals();
	std::shared_ptr<Population> tempPopulation;

	for (int generation = 1; generation <= maxGeneration; generation++)
	{
		for (int population = 0; population < populationsSize; population++)
		{
			tempPopulation = populations[population];
			tempPopulation->sortIndividuals();
			tempPopulation->leaveBest();
			tempPopulation->crossoverAll();
			tempPopulation->tryMutateAll();
			tempPopulation->killChilds();

			// usleep(10000);
			if ((generation -1) % 500 == 0)
			{std::cout << "Generacja numer: " << generation << ". Najlepsze dopasowanie: " << tempPopulation->getBestFitness() << std::endl;
			}
		}
	}
	
	std::cout << tempPopulation->getBestFitness();
}

void Evolution::generatePopulations()
{
	amountOfPopoulations = config->getConfigValue(ConfigInterpreter::POPULATIONS);
	int populations_size = config->getConfigValue(ConfigInterpreter::POPOULATION_SIZE);
	int boundary = config->getConfigValue(ConfigInterpreter::BOUNDARY);
	int mutate = config->getConfigValue(ConfigInterpreter::MUTATE);
	int dimensions = config->getConfigValue(ConfigInterpreter::DIMENSIONS);

	std::shared_ptr<Population> temp;

	for (int i = 0; i < amountOfPopoulations; i++)
	{
		temp = std::make_shared<Population>(populations_size, mutate, boundary, dimensions);
		populations.push_back(temp);
	}
}