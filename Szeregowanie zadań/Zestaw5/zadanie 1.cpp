#include <iostream>
#include <vector>
#include <algorithm>


bool sortingParam(int a, int b) 
{
    return a < b;
}

using namespace std;

int main() 
{
    int m, n;

    cin >> m >> n;

    vector<int> tasks, workers(m,0);

    for (int i = 0; i < n; i++)
    {
        int task;
        cin >> task;
        tasks.push_back(task);
    }

    sort(tasks.begin(), tasks.end(), sortingParam);

    while (tasks.size() > 0)
    {
        sort(workers.begin(), workers.end(), sortingParam);
        workers[0] += tasks.back();
        tasks.pop_back();
    }

    sort(workers.begin(), workers.end(), sortingParam);

    cout << workers[m - 1];
}
