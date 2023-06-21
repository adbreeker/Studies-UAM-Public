#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;



int main() 
{
    int m, n;
    cin >> m >> n;

    vector<int> workers(m,0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int x;
            cin >> x;
            if (j == 0)
            {
                workers[j] += x;
            }
            else
            {
                if (workers[j] < workers[j - 1])
                {
                    workers[j] = workers[j - 1];
                }
                
                workers[j] += x;
            }
        }

        cout << workers.back() << endl;
    }
}
