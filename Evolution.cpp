#include "Evolution.h"
#include "ConfigInterpreter.h"
#include <iostream>

Evolution::Evolution()
{
	config = ConfigInterpreter::getInstance("config.txt");
	maxGeneration = config->getConfigValue(ConfigInterpreter::GENERATIONS);
	migrationPeriod = config->getConfigValue(ConfigInterpreter::MIGRATION_PERIOD);

	generatePopulations();
	run();
}

Evolution::~Evolution()
{
}

void Evolution::run()
{
	int populationsSize = populations.size();
	for(auto& population : populations)
	{
		population->sortIndividuals();
	}
	std::shared_ptr<Population> tempPopulation;

	std::cout << 0 << ";"
		<< populations[0]->getBestFitness() << ";"
		<< populations[0]->getWorstFitness() << ";"
		<< populations[1]->getBestFitness() << ";"
		<< populations[1]->getWorstFitness() <<std::endl;

	for (int generation = 1; generation <= maxGeneration; generation++)
	{
		if (generation % 10 == 0)
		{
			for(int i = 0; i < 2; ++i)
			{
			std::cout << generation << ";"
						<< populations[i]->getBestFitness() << ";"
						<< populations[i]->getWorstFitness();
			}
			std::cout<<std::endl;
		}

		for (int population = 0; population < populationsSize; population++)
		{
			tempPopulation = populations[population];
			
			tempPopulation->leaveBest();
			tempPopulation->crossoverAll();
			tempPopulation->killPredecessors();
			tempPopulation->tryMutateAll();
			tempPopulation->sortIndividuals();
		}

		if (generation % migrationPeriod == 0)
			MigrateAll();
	}
}

void Evolution::generatePopulations()
{
	amountOfPopoulations = config->getConfigValue(ConfigInterpreter::POPULATIONS);
	int populations_size = config->getConfigValue(ConfigInterpreter::POPOULATION_SIZE);
	double boundary = config->getConfigValue(ConfigInterpreter::BOUNDARY)/10;
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

	if(amountOfPopoulations != 2)
	{
		populations[1]->migration(populations[amountOfPopoulations - 1]);
		populations[amountOfPopoulations - 1]->migration(populations[1]);
	}
}