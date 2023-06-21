#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct task
{
    int id;
    vector<int> times;
    int timesSum = 0;
};

bool sortingParam(task& a, task& b)
{
    return a.timesSum >= b.timesSum;
}

int countCmax(vector<task> tasks, int workers)
{
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

vector<task> bestE(vector<vector<task>> allE, int workers)
{
    vector<task> currentBestE = allE[0];
    int currentBestCmax = countCmax(currentBestE, workers);

    for (vector<task> Ek : allE)
    {
        int Cmax = countCmax(Ek, workers);
        if (Cmax < currentBestCmax)
        {
            currentBestE = Ek;
            currentBestCmax = Cmax;
        }
    }

    return currentBestE;
}


int main()
{
    int m, n;
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
            t.timesSum += time;
            t.times.push_back(time);
        }
        tasks.push_back(t);
    }

    sort(tasks.begin(), tasks.end(), sortingParam);

    vector<task> E = tasks;

    for (int j = 0; j < n; j++)
    {
        vector<vector<task>> allE;
        for (int k = 0; k <= j; k++)
        {
            vector<task> Ek;
            for (int places = 0; places < j; places++)
            {
                Ek.push_back(E[places]);
            }
            Ek.insert(Ek.begin() + k, tasks[j]);
            allE.push_back(Ek);
        }
        E = bestE(allE, m);
        
    }

    cout << countCmax(E, m) << endl;
    for (task t : E)
    {
        cout << t.id << " ";
    }
}