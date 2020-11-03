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
	static const std::string TO_CROSS;
	static const std::string MUTATE;


	ConfigInterpreter(std::string fileName);
	int getConfigValue(const std::string& configName);
private:
	std::fstream file;
	std::string fileName;
	std::map<std::string, int> config;
	void openFile();
	void parseConfig();
	std::pair<std::string, int> getSingleConfig(std::string line);
};

