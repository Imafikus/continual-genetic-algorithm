#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <unordered_set>
#include <cmath>


using namespace std;

const int POPULATION_SIZE = 100;
const double EPSILON = 0.1;
const double NUMBER = 2.0;

const int SELECTION = POPULATION_SIZE * 0.4;
const int CROSSOVER = POPULATION_SIZE * 0.3;
const int MUTATION = POPULATION_SIZE * 0.3;

const double LOWER_LIMIT = 0.0;
const double UPPER_LIMIT = 100.0;


random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
uniform_real_distribution<> dis(0.0, 1.0);
std::exponential_distribution<> dis_exp(1);

double cost_function(double x)
{
    return (abs(x*x - NUMBER*NUMBER));
}
double generate_double(double from , double to)
{
    return (to - from) * dis(gen) + to;

}

vector<double> generate_population()
{
    vector<double> p;
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        p.push_back(generate_double(LOWER_LIMIT, UPPER_LIMIT));
    }
    return p;

}
void print_population(vector<double> p)
{
    for(int i = 0; i < p.size(); i++)
        cout << p.at(i) << " ";
    cout << endl;
}

int main()
{
    vector<double> population = generate_population();
    print_population(population);
}


