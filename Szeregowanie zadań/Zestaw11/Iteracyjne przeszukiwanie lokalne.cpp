#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

int m;

struct task
{
    int id;
    vector<int> times;
};


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

pair<int, vector<task>> BestNeighbor(vector<task> x)
{
    pair<int, vector<task>> best;
    bool bestNIL = true;
    for (int i = 0; i <= (int)x.size() - 2; i++)
    {
        for (int j = i + 1; j < (int)x.size(); j++)
        {
            vector<task> y = x;
            task pom = y[i];
            y[i] = y[j];
            y[j] = pom;
            if (bestNIL)
            {
                best = make_pair(countCmax(y), y);
                bestNIL = false;
            }
            else
            {
                int c = countCmax(y);
                if (c < best.first)
                {
                    best = make_pair(c, y);
                }
            }
        }
    }
    return best;
}


pair<int, vector<task>> LocalSearch(vector<task> x)
{
    pair<int, vector<task>> newX = make_pair(countCmax(x), x);
    while (true)
    {
        pair<int, vector<task>> y = BestNeighbor(x);
        if (y.first < newX.first)
        {
            newX = y;
        }
        else
        {
            break;
        }
    }
    
    return newX;

}

pair<int, vector<task>> Perturbate(vector<task> x)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(0, ((int)x.size() - 1));

    for (int k = 0; k < max(5, ((int)x.size() / 20)); k++)
    {
        int i = distribution(gen);
        int j = i;
        while (j == i)
        {
            j = distribution(gen);
        }
        task pom = x[i];
        x[i] = x[j];
        x[j] = pom;
    }

    return make_pair(countCmax(x), x);
}

pair<int, vector<task>> IteratedLocalSearch(vector<task> x)
{
    pair<int, vector<task>> newX = LocalSearch(x);
    pair<int, vector<task>> best = newX;

    for (int i = 0; i < 1000; i++) // warunek końcowy 1000 iteracji (nie zawsze daje najlepsze wyniki przy duzych przykladach)
    {
        pair<int, vector<task>> newXPrim = Perturbate(newX.second);
        newX = LocalSearch(newXPrim.second);
        if (newX.first < best.first)
        {
            best = newX;
        }
    }
    return best;
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

    pair<int, vector<task>> best = IteratedLocalSearch(tasks);

    cout << best.first << endl;
    for (task t : best.second)
    {
        cout << t.id << " ";
    }

}