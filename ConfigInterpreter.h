#pragma once
#include <string>
#include <fstream>
#include <map>

class ConfigInterpreter
{
public:
	static const std::string POPOULATION_SIZE;
	static const std::string ISLANDS_NUMBER;
	static const std::string POPULATIONS;
	static const std::string DIMENSIONS;
	static const std::string BOUNDARY;
	static const std::string GENERATIONS;
	static const std::string MUTATE;
	static const std::string CROSSOVER;
	static const std::string BEST;
	static const std::string MIGRATION;
	static const std::string SIGMA;
	static const std::string MIGRATION_PERIOD;

	static ConfigInterpreter* getInstance(std::string fileName);
	int getConfigValue(const std::string& configName);
	ConfigInterpreter(ConfigInterpreter& clone) = delete;
	
private:
	std::fstream file;
	std::string fileName;
	std::map<std::string, int> config;
	static ConfigInterpreter* _instance;
	
	ConfigInterpreter(std::string fileName);
	void openFile();
	void parseConfig();
	std::pair<std::string, int> getSingleConfig(std::string line);
};

