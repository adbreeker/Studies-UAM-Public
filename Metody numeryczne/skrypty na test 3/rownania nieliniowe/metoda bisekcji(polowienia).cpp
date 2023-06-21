#include <iostream>
#include <cmath>

using namespace std;

double E = 0.000000001;

double f(double x)
{
    return exp(x) - 1.5 - atan(x);
}

void bisekcja(double a, double b)
{
    if (f(a) * f(b) >= 0) {
        cout << "Zly przedzial a b" << endl;
    }
    else
    {
        int k = 1;
        double xk;
        do
        {
            xk = (a + b) / 2;
            if (f(a) * f(xk) < 0)
            {
                a = a;
                b = xk;
            }
            else
            {
                a = xk;
                b = b;
            }

            cout << "Iteracja " << k << ":  " << xk << endl;
            k++;

        } while (abs(f(xk)) > E);
    }

}
// main function
int main() {
    double a, b;
    cout << "Podaj przedzial a b" << endl;
    cin >> a >> b;
    bisekcja(a, b);
}
