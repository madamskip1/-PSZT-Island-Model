#include "ConfigInterpreter.h"
#include <iostream>
#include <sstream>

const std::string ConfigInterpreter::POPOULATION_SIZE = "population_size";
const std::string ConfigInterpreter::ISLANDS_NUMBER = "islands_number";
const std::string ConfigInterpreter::POPULATIONS = "populations";
const std::string ConfigInterpreter::DIMENSIONS = "dimensions";
const std::string ConfigInterpreter::BOUNDARY = "deciboundary";
const std::string ConfigInterpreter::GENERATIONS = "generations";
const std::string ConfigInterpreter::MUTATE = "mutate_chance_per_mille";
const std::string ConfigInterpreter::CROSSOVER = "crossover_percentage";
const std::string ConfigInterpreter::BEST = "best_percentage";
const std::string ConfigInterpreter::MIGRATION = "migration_per_mille";
const std::string ConfigInterpreter::SIGMA = "decisigma";
const std::string ConfigInterpreter::MIGRATION_PERIOD = "migrationPeriod";

ConfigInterpreter * ConfigInterpreter::_instance = nullptr;

ConfigInterpreter* ConfigInterpreter::getInstance(std::string fileName)
{
	if(_instance == nullptr)
		_instance = new ConfigInterpreter(fileName);

	return _instance;
}

ConfigInterpreter::ConfigInterpreter(std::string fileName) : fileName(fileName)
{
	openFile();
}

int ConfigInterpreter::getConfigValue(const std::string& configName)
{
	return config[configName];
}

void ConfigInterpreter::openFile()
{
	file.open(fileName, std::ios::in | std::ios::binary);
	if (file.fail())
	{
	}

	parseConfig();
	file.close();
}

void ConfigInterpreter::parseConfig()
{
	std::pair<std::string, int> temp;
	std::string line;

	while (file >> line)
	{
		temp = getSingleConfig(line);
		config[temp.first] = temp.second;
	}
}

std::pair<std::string, int> ConfigInterpreter::getSingleConfig(std::string line)
{
	std::pair<std::string, int> item;
	std::string delimiter = "=";

	size_t position = line.find(delimiter);

	std::string name = line.substr(0, position);
	std::string tempValue = line.substr(position + 1, line.length() - position - 1);

	item = std::make_pair(name, std::stoi(tempValue));
	return item;
}
