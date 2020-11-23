#pragma once
#include <vector>
#include "ConfigInterpreter.h"
#include "Population.h"

class Evolution
{
public:
	ConfigInterpreter* config{nullptr};
	double bestFtiness{0};
	int maxGeneration{0};
	int migrationPeriod{0};

	Evolution();
	~Evolution();

	void run();

private:
	std::vector<std::shared_ptr<Population>> populations;
	int amountOfPopoulations;

	void MigrateAll();
	void generatePopulations();
};


