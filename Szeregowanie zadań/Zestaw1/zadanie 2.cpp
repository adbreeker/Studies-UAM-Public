#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

bool sortbysec(const pair<int, int>& a,const pair<int, int>& b)
{
    //if (a.second / a.first == b.second / b.first)
    //{
    //    return(a.first < b.first);
    //}
    return ((float)((float)a.first/ (float)a.second) < (float)((float)b.first / (float)b.second));
}

int main()
{
    int n;
    cin >> n;

    vector<pair<int,int>> tab;

    for (int i = 0; i < n; i++)
    {
        int t, c;
        cin >> t >> c;
        tab.push_back(make_pair(t, c));
    }

    sort(tab.begin(), tab.end(), sortbysec);

    long long int sum = 0;
    int days = 0;
    for (pair<int, int> p : tab)
    {
        //cout << p.first << " " << p.second << " " << (float)((float)p.first/ (float)p.second) << endl;
        days += p.first;
        sum += p.second * days;
    }

    cout << sum;

}