#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool sortingParam(int& a, int& b)
{
    return a > b;
}

int chooseMachine(vector<int>& w)
{
    int index = 0;
    int min = w[0];

    for (int i = 1; i < (int)w.size(); i++)
    {
        if (w[i] < min)
        {
            index = i;
            min = w[i];
        }
    }

    return index;
}

int main()
{
    int m, n;
    cin >> m >> n;

    vector<int> machinesSpeed(m);

    for (int i = 0; i < m; i++)
    {
        cin >> machinesSpeed[i];
    }

    vector<int> tasks;

    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        tasks.push_back(t);
    }

    sort(tasks.begin(), tasks.end(), sortingParam);

    vector<int> w = machinesSpeed;

    vector<vector<int>> machinesTasks(m);

    for (int t : tasks)
    {
        int mId = chooseMachine(w);
        w[mId] += machinesSpeed[mId];
        machinesTasks[mId].insert(machinesTasks[mId].begin(), t);
    }

    int sum = 0;

    for (int i = 0; i < m; i++)
    {
        int partSum = 0;
        for (int t : machinesTasks[i])
        {
            partSum += t*machinesSpeed[i];
            sum += partSum;
        }
    }

    cout << sum;
 
}
