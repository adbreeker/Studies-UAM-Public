#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct task 
{
    int id;
    int p1;
    int p2;
};

bool sortingParamA(task& a, task& b)
{
    return a.p1 <= b.p1;
}

bool sortingParamB(task& a, task& b)
{
    return a.p2 >= b.p2;
}


int main() 
{
    int n;
    cin >> n;

    vector<task> A, B;

    for (int i = 0; i < n; i++)
    {
        task t;
        cin >> t.p1 >> t.p2;
        t.id = i + 1;
        if (t.p1 < t.p2)
        {
            A.push_back(t);
        }
        else
        {
            B.push_back(t);
        }
    }

    sort(A.begin(), A.end(), sortingParamA);
    sort(B.begin(), B.end(), sortingParamB);

    int timeP1 = 0, timeP2 = 0;

    for (task t : A)
    {
        timeP1 += t.p1;
        if (timeP2 < timeP1)
        {
            timeP2 = timeP1;
            timeP2 += t.p2;
        }
        else
        {
            timeP2 += t.p2;
        }
        cout << t.id << " " << timeP1 << " " << timeP2 << endl;
    }
    for (task t : B)
    {
        timeP1 += t.p1;
        if (timeP2 < timeP1)
        {
            timeP2 = timeP1;
            timeP2 += t.p2;
        }
        else
        {
            timeP2 += t.p2;
        }
        cout << t.id << " " << timeP1 << " " << timeP2 << endl;
    }

}
