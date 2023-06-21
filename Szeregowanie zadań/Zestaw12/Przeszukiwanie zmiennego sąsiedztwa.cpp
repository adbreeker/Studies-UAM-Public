#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

int m;

struct task
{
    int id;
    vector<int> times;
};


int countCmax(vector<task> tasks)
{
    int workers = m;
    vector<int> workersTimes(workers, 0);
    for (task t : tasks)
    {
        for (int i = 0; i < workers; i++)
        {
            if (i == 0)
            {
                workersTimes[i] += t.times[i];
            }
            else
            {
                if (workersTimes[i] < workersTimes[i - 1])
                {
                    workersTimes[i] = workersTimes[i - 1];
                    workersTimes[i] += t.times[i];
                }
                else
                {
                    workersTimes[i] += t.times[i];
                }
            }
        }
    }
    return workersTimes.back();
}

pair<int, vector<task>> BestNeighbor1(vector<task> x) // zamiana parami
{
    pair<int, vector<task>> best;
    bool bestNIL = true;
    for (int i = 0; i <= (int)x.size() - 2; i++)
    {
        for (int j = i + 1; j < (int)x.size(); j++)
        {
            vector<task> y = x;
            task pom = y[i];
            y[i] = y[j];
            y[j] = pom;
            if (bestNIL)
            {
                best = make_pair(countCmax(y), y);
                bestNIL = false;
            }
            else
            {
                int c = countCmax(y);
                if (c < best.first)
                {
                    best = make_pair(c, y);
                }
            }
        }
    }
    return best;
}

pair<int, vector<task>> BestNeighbor2(vector<task> x) // odwrócenie podciągu
{
    pair<int, vector<task>> best;
    bool bestNIL = true;
    for (int i = 1; i <= (int)x.size() - 1; i++)
    {
        vector<task> y = x;
        reverse(y.begin(), y.begin() + i);

        if (bestNIL)
        {
            best = make_pair(countCmax(y), y);
            bestNIL = false;
        }
        else
        {
            int c = countCmax(y);
            if (c < best.first)
            {
                best = make_pair(c, y);
            }
        }
    }
    return best;
}

pair<int, vector<task>> BestNeighbor3(vector<task> x) // przesunięcie elementu
{
    pair<int, vector<task>> best;
    bool bestNIL = true;
    for (int i = 0; i <= (int)x.size() - 2; i++)
    {
        for (int j = i + 1; j < (int)x.size(); j++)
        {
            vector<task> y = x;
            y.insert(y.begin() + j, y[i]);
            y.erase(y.begin() + i);
            if (bestNIL)
            {
                best = make_pair(countCmax(y), y);
                bestNIL = false;
            }
            else
            {
                int c = countCmax(y);
                if (c < best.first)
                {
                    best = make_pair(c, y);
                }
            }
        }
    }
    return best;
}

pair<pair<int, vector<task>>, int> NeighborChange(pair<int, vector<task>> x, pair<int, vector<task>> xprim, int k)
{
    pair<pair<int, vector<task>>, int> x_k;

    if (xprim.first < x.first)
    {
        x_k = make_pair(xprim, 1);
    }
    else
    {
        x_k = make_pair(x, k+1);
    }

    return x_k;
}

pair<int, vector<task>> LocalSearch(vector<task> x, int neighbor)
{
    pair<int, vector<task>> newX = make_pair(countCmax(x), x);
    while (true)
    {
        pair<int, vector<task>> y;

        if (neighbor == 1) { y = BestNeighbor1(x); }
        if (neighbor == 2) { y = BestNeighbor2(x); }
        if (neighbor == 3) { y = BestNeighbor3(x); }

        if (y.first < newX.first)
        {
            newX = y;
        }
        else
        {
            break;
        }
    }

    return newX;

}

pair<int, vector<task>> VND(vector<task> x, int kmax)
{
    int k = 1;
    vector<task> newX = x;

    while (k <= kmax)
    {
        pair<int, vector<task>> xprim;
        if (k == 1) { xprim = BestNeighbor1(newX); }
        if (k == 2) { xprim = BestNeighbor2(newX); }
        if (k == 3) { xprim = BestNeighbor3(newX); }

        pair<pair<int, vector<task>>, int> x_k = NeighborChange(make_pair(countCmax(newX), newX), xprim, k);

        newX = x_k.first.second;
        k = x_k.second;
    }

    return make_pair(countCmax(newX), newX);
}

pair<int, vector<task>> BVNS(vector<task> x, int kmax)
{
    vector<task> newX = x;
    for (int i = 0; i < 1000; i++) // warunek stopu 100 powtorzen
    {
        int k = 1;
        while (k <= kmax)
        {
            pair<int, vector<task>> xprim1;
            if (k == 1) { xprim1 = BestNeighbor1(newX); }
            if (k == 2) { xprim1 = BestNeighbor2(newX); }
            if (k == 3) { xprim1 = BestNeighbor3(newX); }

            pair<int, vector<task>> xprim2 = LocalSearch(newX, k);

            pair<pair<int, vector<task>>, int> x_k = NeighborChange(xprim1, xprim2, k);
            newX = x_k.first.second;
            k = x_k.second;
        }
    }

    return make_pair(countCmax(newX), newX);
}


int main()
{
    int n;
    cin >> m >> n;
    vector<task> tasks;
    for (int i = 0; i < n; i++)
    {
        task t;
        t.id = i + 1;
        for (int j = 0; j < m; j++)
        {
            int time;
            cin >> time;
            t.times.push_back(time);
        }
        tasks.push_back(t);
    }

    pair<int, vector<task>> best = VND(tasks, 3);

    //pair<int, vector<task>> best = BVNS(tasks, 3);

    cout << best.first << endl;
    for (task t : best.second)
    {
        cout << t.id << " ";
    }

}