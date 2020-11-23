#include "Individual.h"
#include "RandomNumber.h"
#include <cmath>
#include <iostream>
#include <algorithm>
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
    // ackley();
    rastrigin();
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

void Individual::setValues(std::vector<double> values)
{
    this->values = values;
}

std::vector<double> Individual::getValues()
{
    return values;
}

void Individual::mutate(const double & mutateOp, int position)
{
    values[position] += mutateOp;
    std::clamp(values[position], -mutateOp, mutateOp);
    calculateFitness();
}

void Individual::migrate(const Individual& other)
{
    values = other.values;
}

void Individual::ackley()
{
    double firstSum{0};
    double secondSum{0};
    double dimensions = values.size();
    double result{0};

    for(int i=0; i < dimensions; ++i)
    {
        firstSum += values[i] * values[i];
        secondSum += std::cos(2*PI*values[i]);
    }

    result = -20 * std::exp(- 0.2 * std::sqrt(1/dimensions * firstSum));
    result -= std::exp(1/dimensions * secondSum);
    result += 20 + std::exp(1);

    fitness = result;
}

void Individual::rastrigin()
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