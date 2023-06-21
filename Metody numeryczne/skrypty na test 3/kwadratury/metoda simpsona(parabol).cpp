#include<iostream>
#include<math.h>


using namespace std;

double f(double x)
{
    if(x<0.5)
        return -1;
    if(x<1)
        return -0.25;
    if(x<1.5)
        return 2;
    if(x<2)
        return 5.75;
    if(x>=2)
        return 11;
}

int main()
{
    double a, b, h, kwadratura, skladowa_suma = 0;
    int n;

    cout << "Podaj przedzialy a b" << endl;
    cin >> a >> b;
    cout << "Podaj krok h" << endl;
    cin >> h;

    n = (b - a) / h;

    for (int i = 1; i <= n - 1; i++)
    {
        if (i % 2 == 0)
        {
            skladowa_suma = skladowa_suma + 2 * (f(a + i * h));
        }
        else
        {
            skladowa_suma = skladowa_suma + 4 * (f(a + i * h));
        }

    }

    kwadratura = (h / 3) * (f(a) + skladowa_suma + f(b));

    cout << endl << "Przyblizona wartosc calki to: " << kwadratura;

}

