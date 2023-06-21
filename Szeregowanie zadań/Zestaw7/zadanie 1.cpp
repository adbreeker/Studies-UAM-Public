#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int main()
{
    int n;
    cin >> n;

    float sum = 0.0;
    int Cmax = 0;

    vector<int> p(n+1);
    for (int i = 1; i <= n; i++)
    {
        int t;
        cin >> t;
        p[i] = t;
        sum += static_cast<float>(t) / 2.0;
        Cmax += t;
    }

    int B = static_cast<int>(sum);

    vector<vector<bool>> A(n+1, vector<bool>(B+1));

    for (int i = 0; i <= n; i++)
    {
        A[i][0] = true;
    }

    for (int j = 1; j <= B; j++)
    {
        A[0][j] = false;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= B; j++)
        {
            A[i][j] = A[i-1][j];
            if (p[i] <= j)
            {
                A[i][j] = A[i][j] || A[i - 1][j - p[i]];
            }
        }
    }

    int C = 0;

    for (int j = B; j >= 0; j--)
    {
        if (A[n][j])
        {
            C = j;
            break;
        }
    }

    Cmax = Cmax - C;
    cout << C << " " << Cmax << endl;


}
