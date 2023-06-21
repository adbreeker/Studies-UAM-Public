#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

// Jako że bardzo mi się podoba zamysł algorytmów genetycznych postanowiłem napisać go bez zaglądania w żadne gotowe algorytmy (również te z wykładu), 
// a jedynie bazując na wyobrażeniu jak powinien on wyglądać po zajeciach ze sztucznej inteligencji, także za wszelkie niedociągnięcia czy błędy w sztuce z góry przepraszam.

using namespace std;

int m;

struct task
{
    int id;
    vector<int> times;
};

// additional functions --------------------------------------------------------------------- additional functions

int countCmax(vector<task> tasks)
{
    int workers = m;
    vector<int> workersTimes(workers,0);
    for (task t : tasks)
    {
        for (int i = 0; i < workers; i++)
        {
            if (i == 0)
            {
                workersTimes[i] += t.times[i];
            }
            else
            {
                if (workersTimes[i] < workersTimes[i - 1])
                {
                    workersTimes[i] = workersTimes[i - 1];
                    workersTimes[i] += t.times[i];
                }
                else
                {
                    workersTimes[i] += t.times[i];
                }
            }
        }
    }
    return workersTimes.back();
}

bool FindTask(task t, vector<task> tasks)
{
    for (task check : tasks)
    {
        if (check.id == t.id)
        {
            return true;
        }
    }

    return false;
}

bool SortingPopulation(pair<int, vector<task>>& a, pair<int, vector<task>>& b)
{
    return a.first < b.first;
}

// generating first population ------------------------------------------------------------------------------------------------------------------ generating first population

vector<task> RandomSpeciment(vector<task> tasks)
{
    random_device rd;
    mt19937 gen(rd());
    

    vector<task> newRandomSpeciment;
    while (tasks.size() > 0)
    {
        uniform_int_distribution<> distribution(0, ((int)tasks.size() - 1));

        int tID = distribution(gen);
        newRandomSpeciment.push_back(tasks[tID]);

        tasks.erase(tasks.begin() + tID);
    }

    return newRandomSpeciment;
}

vector<pair<int, vector<task>>> MakeFirstPopulation(vector<task> tasks) //populacje liczą sobie 100 osobników
{
    vector<pair<int, vector<task>>> population;

    for (int i = 0; i < 100; i++)
    {
        vector<task> newSpeciment = RandomSpeciment(tasks);

        population.push_back(make_pair(countCmax(newSpeciment), newSpeciment));
    }

    sort(population.begin(), population.end(), SortingPopulation);

    return population;
}

// crossovers ------------------------------------------------------------------------------------------------------------------------------------------ crossovers

pair<vector<task>, vector<task>> CrossoverParents(vector<task> parent1, vector<task> parent2)
{

    // dziecko A = połowa zadań rodzica A + niebędąca w dziecku druga połowa zadań rodzica B + po kolei wszystkie zadania rodzica B które jeszcze nie są w dziecku A
    // w ten sposób oboje dzieci (o ile rodzice są rózni) rózni się od siebie, mając jednocześnie wszystkie zadania jakie są do zrobienia (każde występujące raz)

    vector<task> child1(parent1.begin(), parent1.begin() + parent1.size() / 2);
    vector<task> child2(parent2.begin(), parent2.begin() + parent2.size() / 2);

    for (int i = parent2.size() / 2 + 1; i < (int)parent2.size(); i++)
    {
        if (!FindTask(parent2[i], child1))
        {
            child1.push_back(parent2[i]);
        }
    }
    for (task t : parent2)
    {
        if (!FindTask(t, child1))
        {
            child1.push_back(t);
        }
    }


    for (int i = parent1.size() / 2 + 1; i < (int)parent1.size(); i++)
    {
        if (!FindTask(parent1[i], child2))
        {
            child2.push_back(parent1[i]);
        }
    }
    for (task t : parent1)
    {
        if (!FindTask(t, child2))
        {
            child2.push_back(t);
        }
    }


    return make_pair(child1, child2);
}

vector<pair<int, vector<task>>> CrossoverPopulation(vector<pair<int, vector<task>>> population)
{
    // krzyżowana jest lepsza połowa populacji, gorsza zastępowana jest dziećmi lepszej

    vector<pair<int, vector<task>>> children;
    for (int i = 0; i < (int)population.size(); i+=2)
    {
        pair<vector<task>, vector<task>> offsprings = CrossoverParents(population[i].second, population[i + 1].second);
        children.push_back(make_pair(countCmax(offsprings.first), offsprings.first));
        children.push_back(make_pair(countCmax(offsprings.second), offsprings.second));
    }

    return children;

}

// mutations ---------------------------------------------------------------------------------------------------------------------------------------------- mutations

vector<pair<int, vector<task>>> MutatePopulation(vector<pair<int, vector<task>>> population, int numberOfMutations)
{
    random_device rd;
    mt19937 gen(rd());

    //w mojej wersji najsilniejszy przedstawiciel gatunku jest odporny na mutacje aby nigdy nie nastąpiła "ewolucja wsteczna"
    uniform_int_distribution<> distribution(1, ((int)population.size() - 1));

    for (int i = 0; i < numberOfMutations; i++)
    {
        int specimentID = distribution(gen);

        uniform_int_distribution<> taskID(0, ((int)population[specimentID].second.size() - 1));
        int t1ID = taskID(gen);
        int t2ID = taskID(gen);

        task pom = population[specimentID].second[t1ID];
        population[specimentID].second[t1ID] = population[specimentID].second[t2ID];
        population[specimentID].second[t2ID] = pom;

        population[specimentID].first = countCmax(population[specimentID].second);
    }
    

    return population;
}

// genetic algorithm itself ---------------------------------------------------------------------------------------------------------------------- genetic algorithm itself

pair<int, vector<task>> GeneticAlgorithm(vector<task> startingTasks, int generationsLimit, bool showGenerationBest)
{
    vector<pair<int, vector<task>>> population = MakeFirstPopulation(startingTasks);

    for (int generations = 1; generations <= generationsLimit; generations++)
    {
        vector<pair<int, vector<task>>> strongerHalfOfPopulation(population.begin(), population.begin() + population.size() / 2);
        vector<pair<int, vector<task>>> children = CrossoverPopulation(strongerHalfOfPopulation);

        vector<pair<int, vector<task>>> nextGenPopulation = strongerHalfOfPopulation;
        nextGenPopulation.insert(nextGenPopulation.end(), children.begin(), children.end());

        nextGenPopulation = MutatePopulation(nextGenPopulation , 8);

        sort(nextGenPopulation.begin(), nextGenPopulation.end(), SortingPopulation);
        population = nextGenPopulation;

        if (showGenerationBest)
        {
            cout << "Generation " << generations << ", best speciment: " << population[0].first << endl;
        }
    }

    return population[0];
}

int main()
{
    int n;
    cin >> m >> n;
    vector<task> tasks;
    for (int i = 0; i < n; i++)
    {
        task t;
        t.id = i + 1;
        for (int j = 0; j < m; j++)
        {
            int time;
            cin >> time;
            t.times.push_back(time);
        }
        tasks.push_back(t);
    }

    pair<int, vector<task>> best = GeneticAlgorithm(tasks, 300, false); // przy zamienieniu opcji na true, dodatkowy wykaz jak zmienial sie najlepszy osobnik na tle generacji.

    cout << best.first << endl;
    for (task t : best.second)
    {
        cout << t.id << " ";
    }

}