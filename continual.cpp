#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <unordered_set>
#include <cmath>


using namespace std;

const int POPULATION_SIZE = 10;
const double EPSILON = 0.1;
const double NUMBER = 2.0;

const int SELECTION = 4;
const int CROSSOVER = 3;
const int MUTATION = 3;

const double LOWER_LIMIT = 0.0;
const double UPPER_LIMIT = 10.0;

///random, better than rand()
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
///tournament style selection, it does not take already selected chromosome
vector<double> selection(vector<double> pop)
{
    ///keeps indexes of already selected chromosomes
    unordered_set<int> already_selected;


    int selection_limit = POPULATION_SIZE - SELECTION;

    for(int i = 0; i < selection_limit; i++)
    {
        int idx1;
        do{
            idx1 = rand() % POPULATION_SIZE;
        }while(already_selected.count(idx1) != 0);

        int idx2;
        do{
            idx2 = rand() % POPULATION_SIZE;
        }while(already_selected.count(idx2) != 0);


        int better_chrom;

        if( cost_function(pop.at(idx1)) <= cost_function(pop.at(idx2)) ) better_chrom = idx1;
        else better_chrom = idx2;

        already_selected.insert(better_chrom);
    }
    vector<double> select;
    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        if(already_selected.count(i) == 0)
        select.push_back(pop.at(i));
    }
    return select;
}


int main()
{
    srand(time(NULL));
    vector<double> population = generate_population();
    vector<double> select = selection(population);
    print_population(population);
    print_population(select);
}


