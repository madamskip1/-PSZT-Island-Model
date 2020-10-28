#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../ConfigInterpreter.h"

TEST_CASE("Config parser test", "[config]")
{
	ConfigInterpreter parser("UnitTests/configTestFile.txt");
	int population_size = parser.getConfigValue(ConfigInterpreter::POPOULATION_SIZE);
	int islands_number = parser.getConfigValue(ConfigInterpreter::ISLANDS_NUMBER);

	REQUIRE(population_size == 10);
	REQUIRE(islands_number == 5);
}