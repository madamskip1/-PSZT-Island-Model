#include "Individual.h"
#include <cmath>
#include "RandomNumber.h"
#include <iostream>
#define PI 3.14159265358979323846

double Individual::boundary = 0;

Individual::Individual(double value) : fitness(0)
{
    values.push_back(value);
    calculateFitness();
    std::cout << fitness << std::endl;
}

Individual::Individual(std::vector<double> values) : fitness(0), values(values)
{
    calculateFitness();
}

void Individual::calculateFitness()
{
    int A = 10;
    int dimensions = values.size();
    double result = 0;
    double x;

    for (int i = 0; i < dimensions; i++)
    {
        x = values[i];

        result += x * x - 10 * cos(2 * PI * x);
    }

     result += 10 * dimensions;

     fitness = result;
}

double Individual::getFitness()
{
    return fitness;
}

double Individual::getValue(int dimension)
{
    return values[dimension];
}

void Individual::setValue(int dimension, double value)
{
    values[dimension] = value;
    calculateFitness();
}

std::vector<double> Individual::getValues()
{
    return values;
}

void Individual::mutate(const double & mutateOp, int position)
{
    values[position] += mutateOp;
    calculateFitness();
}

void Individual::migrate(const Individual& other)
{
    values = other.values;
}
