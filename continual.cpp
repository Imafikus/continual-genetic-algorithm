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
const double UPPER_LIMIT = 5.0;

const int ITERATIONS = 1000000;

///random, better than rand()
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0, 1.0);
std::exponential_distribution<> dis_exp(1);

double cost_function(double x)
{
    return (abs(x*x - NUMBER));
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
///tournament style selection, it does not take already selected chromosomes
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

vector<double> crossover(vector<double> pop)
{
    vector<double> cross;

    for(int i = 0; i < CROSSOVER; i++)
    {
        int idx1 = rand() % SELECTION;
        int idx2 = rand() % SELECTION;

        double ratio = generate_double(0.0, 1.0);

        double new_chromosome = (pop.at(idx2) - pop.at(idx1)) * ratio + pop.at(idx1);
        cross.push_back(new_chromosome);
    }
  return cross;
}
vector<double> mutation(vector<double> pop)
{
    vector<double> mutate;

    for(int i = 0; i < MUTATION; i++)
    {
      int idx1 = rand() % SELECTION;

      double new_chromosome = pop.at(idx1) + generate_double(-0.1, 0.1) * pop.at(idx1);
      mutate.push_back(new_chromosome);
    }
    return mutate;
}
void make_new_population(vector<double> &population, vector<double> select, vector<double> cross, vector<double> mutate)
{
    for(int i = 0; i < SELECTION; i++)
        population.at(i) = select.at(i);

    for(int i = 0; i < CROSSOVER; i++)
          population.at(i) = cross.at(i);

    for(int i = 0; i < MUTATION; i++)
        population.at(i) = cross.at(i);
}
int main()
{
    srand(time(NULL));
    vector<double> population = generate_population();

    cout << "Starting population... \n";
    print_population(population);

    for(int j = 0; j < ITERATIONS; j++)
    {
        vector<double> select = selection(population);
        vector<double> cross = crossover(select);
        vector<double> mutate = mutation(select);

        make_new_population(population, select, cross, mutate);
    }
    print_population(population);

    sort(population.begin(), population.end());
    double best_fit = population.at(0);
    cout << "Best fit: " << best_fit << endl;
    /*print_population(population);
    print_population(select);
    print_population(cross);
    print_population(mutate);
    */
}
