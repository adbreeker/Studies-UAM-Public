#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool sortingParam(const pair<int,int>& a, const pair<int,int>& b)
{
	return a.second< b.second;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int,int>> tasks;
    for(int i=0; i<n; i++)
    {
        int a,b;
        cin >> a >> b;
        tasks.push_back(make_pair(a,b));
    }
    
    sort(tasks.begin(), tasks.end(), sortingParam);
    
    int currentTime = 0;
    int maxDelay = -1000;
    for(pair<int,int> task : tasks)
    {
        currentTime += task.first;
        int delay = currentTime - task.second;
        if(delay > maxDelay)
        {
            maxDelay = delay;
        }
    }
    
    cout << maxDelay;
}