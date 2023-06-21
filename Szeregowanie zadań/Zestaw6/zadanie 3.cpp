#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct task
{
    int time;
    int bonus;
};

bool sortingParam(task& a, task& b)
{
    return a.time < b.time;
}

pair<int, int> lowestBonusTask(vector<vector<task>>& workers)
{
    int lowestBonus = workers[0][0].bonus;
    int worker = 0;
    int taskId = 0;
    for (int i = 0; i < (int)workers.size(); i++)
    {
        for (int j = 0; j < (int)workers[i].size(); j++)
        {
            if (workers[i][j].bonus < lowestBonus)
            {
                lowestBonus = workers[i][j].bonus;
                worker = i;
                taskId = j;
            }
        }
    }

    return make_pair(worker, taskId);
}


int main()
{
    int m, n;
    cin >> m >> n;

    vector<task> tasks;
    for (int i = 0; i < n; i++)
    {
        task t;
        cin >> t.bonus >> t.time;
        tasks.push_back(t);
    }

    sort(tasks.begin(), tasks.end(), sortingParam);

    vector<vector<task>> workers(m);

    vector<int> workersTime(m,0);

    int sum = 0;

    for (task t : tasks)
    {
        bool taskAsigned = false;
        for (int i = 0; i < m; i++)
        {
            if (workersTime[i] < t.time)
            {
                workersTime[i] += 1;
                workers[i].push_back(t);
                taskAsigned = true;
                break;
            }
        }

        if (!taskAsigned)
        {
            pair<int, int> lbt = lowestBonusTask(workers);
            if (workers[lbt.first][lbt.second].bonus < t.bonus)
            {
                sum += workers[lbt.first][lbt.second].bonus;
                workers[lbt.first][lbt.second] = t;
            }
            else
            {
                sum += t.bonus;
            }
        }
    }

    

    cout << sum;

}
