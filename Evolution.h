#pragma once
#include <vector>
#include "ConfigInterpreter.h"
#include "Population.h"

class Evolution
{
public:
	double bestFtiness;
	ConfigInterpreter* config;
	//int generation;
	int maxGeneration;

	Evolution();
	~Evolution();


	void run();

private:
	std::vector<std::shared_ptr<Population>> populations;
	int amountOfPopoulations;

	void generatePopulations();
};

