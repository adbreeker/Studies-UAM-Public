#include<iostream>
#include<math.h>

using namespace std;

double f(double x)
{
	return pow(x, 2);
}


int main()
{
	double a, b, h, kwadratura, skladowa_suma=0;
	int n;

	cout << "Podaj przedzialy a b" << endl;
	cin >> a >> b;
	cout << "Podaj krok h" << endl;
	cin >> h;

	n = (b - a) / h;

	for (int i = 1; i <= n-1; i++)
	{
		skladowa_suma = skladowa_suma + (f(a + i * h));
	}

	kwadratura = (h/2) * (f(a) + 2 * skladowa_suma + f(b));

	cout << endl << "Przyblizona wartosc calki to: " << kwadratura;
}
