#include <iostream>
#include <cmath>

using namespace std;

double E = 0.000001;

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
        double xk1, xk, xk_1;
        xk = b;
        xk_1 = a;
        do
        {
            xk1 = xk - (f(xk) * ((xk - xk_1) / (f(xk) - f(xk_1))));
            xk_1 = xk;
            xk = xk1;

            cout << "Iteracja " << k << " czyli x" << k+1 <<":  " << xk1 << endl;
            k++;

        } while (abs(f(xk1)) > E);
    }

}
// main function
int main() {
    double a, b;
    cout << "Podaj przedzial a b" << endl;
    cin >> a >> b;
    bisekcja(a, b);
}
