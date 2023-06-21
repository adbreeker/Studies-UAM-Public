#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool sortingParam(int& a, int& b)
{
    return a < b;
}

int main()
{
    int m, n;
    cin >> m >> n;

    vector<int> tasks;

    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        tasks.push_back(t);
    }

    sort(tasks.begin(), tasks.end(), sortingParam);

    vector<int> machines(m,0);

    int sum = 0;
    int mId = 0;
    for (int t : tasks)
    {
        machines[mId] += t;
        sum += machines[mId];

        mId++;
        if (mId == m)
        {
            mId = 0;
        }
    }

    cout << sum;


}
