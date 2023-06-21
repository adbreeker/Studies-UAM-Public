#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct task 
{
    int time;
    int points;
};

bool sortingParam(task& a, task& b)
{
    return a.time * b.points > b.time * a.points;
}

int maxPoints(vector<task>& tasks, vector<vector<int>>& dp, int deadline, int current_task) 
{
    if (current_task < 0) 
    {
        return 0;
    }

    if (dp[current_task][deadline] != -1) 
    {
        return dp[current_task][deadline];
    }

    int points_if_skipped = maxPoints(tasks, dp, deadline, current_task - 1);

    if (tasks[current_task].time <= deadline) 
    {
        int points_if_completed = tasks[current_task].points + maxPoints(tasks, dp, deadline - tasks[current_task].time, current_task - 1);
        dp[current_task][deadline] = max(points_if_skipped, points_if_completed);
    }
    else 
    {
        dp[current_task][deadline] = points_if_skipped;
    }

    return dp[current_task][deadline];
}

int main() 
{
    int n, d;
    cin >> n >> d;
    vector<task> tasks(n);

    for (int i = 0; i < n; i++) 
    {
        cin >> tasks[i].time >> tasks[i].points;
    }

    vector<vector<int>> dp(n, vector<int>(d + 1, -1));

    sort(tasks.begin(), tasks.end(), sortingParam);

    cout << maxPoints(tasks, dp, d, n - 1) << endl;
}
