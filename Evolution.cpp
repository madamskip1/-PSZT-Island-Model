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
	for(auto population : populations)
	{
		population->sortIndividuals();
	}
	std::shared_ptr<Population> tempPopulation;

	for (int generation = 1; generation <= maxGeneration; generation++)
	{
		for (int population = 0; population < populationsSize; population++)
		{
			tempPopulation = populations[population];
			tempPopulation->sortIndividuals();
			tempPopulation->leaveBest();
			tempPopulation->crossoverAll();
			tempPopulation->killChildren();
			tempPopulation->tryMutateAll();

			}

			if (generation % 10 == 0)
			{
				std::cout<<generation<<";";
				for(int i=0; i<2; ++i)
				{
				std::cout << i << ";"
						  << populations[i]->getBestFitness() << ";"
						  << populations[i]->getWorstFitness() << ";";
				}
				std::cout<<std::endl;
		}
		if(generation % 5)
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
	for(int i=0;i < amountOfPopoulations-3 ;++i)
	{
		populations[i%(amountOfPopoulations-3)+1]->migration(*populations[i%(amountOfPopoulations-3)+2]);
		populations[i%(amountOfPopoulations-3)+2]->migration(*populations[i%(amountOfPopoulations-3)+1]);
	}
}