#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct task
{
    int id;
    int time;
    int points;
    int deadline;
};

bool sortingParam(task& a, task& b)
{
    if (a.deadline == b.deadline)
    {
        return a.id < b.id;
    }
    return a.deadline <= b.deadline;
}

int main()
{
    int n, deadline;
    cin >> n >> deadline;
    
    vector<task> tasks;
    for (int i = 0; i < n; i++)
    {
        task ta;
        cin >> ta.time >> ta.points;
        ta.deadline = deadline;
        ta.id = i + 1;
        tasks.push_back(ta);
    }

    sort(tasks.begin(), tasks.end(), sortingParam);

    vector <vector<int>> F(n + 1, vector<int>(tasks.back().deadline + 1));

    for (int j = 0; j <= n; j++)
    {
        for (int t = 0; t <= tasks.back().deadline; t++)
        {
            if (j == 0)
            {
                F[j][t] = 0;
            }
            else
            {
                if (t == 0)
                {
                    int sum = 0;
                    for (int i = 0; i < j; i++)
                    {
                        sum += tasks[i].points;
                    }
                    F[j][t] = sum;
                }
                else
                {
                    if (t <= tasks[j-1].deadline)
                    {
                        if (t >= tasks[j - 1].time)
                        {
                            F[j][t] = min(F[j - 1][t - tasks[j - 1].time], F[j - 1][t] + tasks[j - 1].points);
                        }
                        else
                        {
                            F[j][t] = F[j - 1][t] + tasks[j - 1].points;
                        }
                    }
                    else
                    {
                        F[j][t] = F[j][tasks[j - 1].deadline];
                    }
                }
            }
        }
    }

    int t = tasks.back().deadline;
    vector<int> lateTasks;
    for (int j = n; j >= 1; j--)
    {
        t = min(t, tasks[j - 1].deadline);
        if (F[j][t] == (F[j - 1][t] + tasks[j - 1].points))
        {
            lateTasks.push_back(j);
        }
        else
        {
            t = t - tasks[j - 1].time;
        }
    }

    vector<task> notLateTasks;

    long long int pointsGained = 0;
    for (task ta : tasks)
    {
        if (find(lateTasks.begin(), lateTasks.end(), ta.id) == lateTasks.end())
        {
            pointsGained += ta.points;
            notLateTasks.push_back(ta);
        }
    }

    sort(notLateTasks.begin(), notLateTasks.end(), sortingParam);

    cout << pointsGained << endl;
    for (task ta : notLateTasks)
    {
        cout << ta.id << endl;
    }
}
