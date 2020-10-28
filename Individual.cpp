#include "Individual.h"
#include <cmath>
#include "RandomNumber.h"
#define PI 3.14159265358979323846

double Individual::boundary = 0;

Individual::Individual(double value) : fitness(0)
{
    values.push_back(value);
    calculateFitness();
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

}

double Individual::getFitness()
{
    return fitness;
}

double Individual::getValue(int dimension)
{
    return values[dimension - 1];
}

std::vector<double> Individual::getValues()
{
    return values;
}

void Individual::mutate(const double &standardDeviation)
{
    int dimensions = values.size() - 1;
    int dimension = RandomNumber::getInstance()->randomInt(0, dimensions);

    values[dimension] += standardDeviation;
    calculateFitness();
}

double Individual::sumOfValues()
{
    double result;
    for (int i = 0; i < values.size(); i++)
        result += values[i];

    return result;
}

double Individual::avgOfValues()
{
    double result = sumOfValues();

    return result / values.size();
}