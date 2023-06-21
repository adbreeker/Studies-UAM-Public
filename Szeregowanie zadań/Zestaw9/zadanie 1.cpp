#include <iostream>
#include <algorithm>

using namespace std;



int main() 
{
    int n;
    cin >> n;

    int sumA = 0, sumB = 0, maxSumAB = 0;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        sumA += a;
        sumB += b;

        if (a + b > maxSumAB)
        {
            maxSumAB = a + b;
        }
    }

    cout << max(max(sumA, sumB), maxSumAB);
}
