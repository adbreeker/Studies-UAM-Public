#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 105;

int n, e;
int t[MAXN];
int in_degree[MAXN];
vector<int> adj[MAXN];

int main() 
{
    cin >> n >> e;

    for (int i = 1; i <= n; i++) 
    {
        cin >> t[i];
    }

    for (int i = 0; i < e; i++) 
    {
        int k, l;
        cin >> k >> l;
        adj[k].push_back(l);
        in_degree[l]++;
    }

    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 1; i <= n; i++) 
    {
        if (in_degree[i] == 0) 
        {
            q.push(i);
        }
    }

    int total_time = 0;

    while (!q.empty()) 
    {
        int u = q.top();
        q.pop();
        cout << u << endl;
        total_time += t[u];

        for (int v : adj[u]) 
        {
            in_degree[v]--;
            if (in_degree[v] == 0) 
            {
                q.push(v);
            }
        }
    }

    cout << total_time << endl;

    return 0;
}