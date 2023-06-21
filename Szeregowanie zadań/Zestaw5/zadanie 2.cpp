#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct task
{
    int taskId;
    int timeStart;
    int timeStop;
};

int Cmax(vector<int> times, int m)
{
    int cmax = 0;
    int sum = 0;
    for (int x : times)
    {
        sum += x;

        if (x > cmax)
        {
            cmax = x;
        }
    }

    return max(sum / m, cmax);
}

using namespace std;

int main()
{
    int n, m;

    cin >> m >> n;

    vector<int> tasksTimes;

    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        tasksTimes.push_back(t);
    }

    int cmax = Cmax(tasksTimes, m);

    cout << cmax << endl;

    vector<vector<task>> workers(m);

    int t = 0;
    int i = 0;
    for (int j = 1; j <= n; j++)
    {
        if (t + tasksTimes[j - 1] <= cmax)
        {
            task ta;
            ta.taskId = j;
            ta.timeStart = t;
            ta.timeStop = t + tasksTimes[j - 1];
            workers[i].push_back(ta);
            t = t + tasksTimes[j - 1];
        }
        else
        {
            task t1;
            t1.taskId = j;
            t1.timeStart = t;
            t1.timeStop = cmax;
            if (t1.timeStart != t1.timeStop)
            {
                workers[i].push_back(t1);
            }
            
            task t2;
            t2.taskId = j;
            t2.timeStart = 0;
            t2.timeStop = tasksTimes[j - 1] - (cmax - t);
            workers[i + 1].push_back(t2);

            i++;
            t = tasksTimes[j - 1] - (cmax - t);
        }
    }

    for (int w = 0; w < m; w++)
    {
        cout << w + 1 << ": ";
        for (task t : workers[w])
        {
            cout << t.taskId << "[" << t.timeStart << "," << t.timeStop << "] ";
        }
        cout << endl;
    }

}
