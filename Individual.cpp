#include "Individual.h"

double Individual::boundary = 0;

Individual::Individual(int value) : value(value), fitness(0)
{
}

int Individual::getValue()
{
    return value;
}

void Individual::mutate(const double &standardDeviation)
{
    value += standardDeviation;
    // calculate fitnesse
}
