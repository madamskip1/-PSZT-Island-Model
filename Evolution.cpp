#include "Evolution.h"
#include "ConfigInterpreter.h"
#include <iostream>


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
	for(auto& population : populations)
	{
		population->sortIndividuals();
	}
	std::shared_ptr<Population> tempPopulation;

	for (int generation = 1; generation <= maxGeneration; generation++)
	{
		for (int population = 0; population < populationsSize; population++)
		{
			tempPopulation = populations[population];
			
			tempPopulation->leaveBest();
			tempPopulation->crossoverAll();
			tempPopulation->killChildren();
			tempPopulation->tryMutateAll();
			tempPopulation->sortIndividuals();
		}

		if (generation % 10 == 0)
		{
			std::cout<<generation<<";";
			for(int i = 0; i < 2; ++i)
			{
			std::cout << i << ";"
						<< populations[i]->getBestFitness() << ";"
						<< populations[i]->getWorstFitness() << ";";
			}
			std::cout<<std::endl;
		}

		if (generation % 5)
			MigrateAll();
	}
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

void Evolution::MigrateAll()
{
	int indexTo;
	for (int i = 1; i < amountOfPopoulations - 1; i++)
	{
		populations[i]->migration(populations[i + 1]);
	}

	for (int i = amountOfPopoulations - 1; i > 1; i--)
	{
		populations[i]->migration(populations[i - 1]);
	}

	populations[1]->migration(populations[amountOfPopoulations - 1]);
	populations[amountOfPopoulations - 1]->migration(populations[1]);
}