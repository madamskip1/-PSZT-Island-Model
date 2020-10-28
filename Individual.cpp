#include "Individual.h"

Individual::Individual(int value) : value(value), fitness(0)
{
}

int Individual::getValue()
{
    return value;
}
