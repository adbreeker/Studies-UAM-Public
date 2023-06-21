#include <iostream>

using namespace std;

// podstawowy rozmiar tablicy ilorazow roznicowych, dla wiecej niz 100 wartosci nalezy zwiekszyc rozmiar
const int tabsize = 100;

double iloraz_roznicowy(double x1, double x2, double fx1, double fx2)
{
    double wynik = (fx2 - fx1) / (x2 - x1);
    return wynik;
}

int main()
{
    // tworzenie tabeli wartoci ilorazow roznicowych
    int n;
    cout << "podaj liczbe wartosci" << endl;
    cin >> n;
    double tab[tabsize][tabsize];
    for (int j = 0; j < n; j++)
    {
        cout << "podaj punkt oraz wartosc f w tym punkcie" << endl;
        double x, fx;
        cin >> x;
        tab[0][j] = x;
        cin >> fx;
        tab[1][j] = fx;
    }

    for (int i = 2; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1 - i; j++)
        {
            tab[i][j] = iloraz_roznicowy(tab[0][j], tab[0][j + 1 + (i - 2)], tab[i - 1][j], tab[i - 1][j + 1]);
        }
    }

    // wypisuje tabele wartosci ilorazow ró¿nicowych (nie jest to potrzebne w tym skrypcie ale uzna³em ¿e ca³kiem przydatne)
    cout << endl << "xi:      ";
    for (int j = 0; j < n;j++)
    {
        cout << tab[0][j] << " | ";
    }
    for (int i = 1; i < n + 1; i++)
    {
        cout << endl << "fxi +" << i-1 << ":  ";
        for (int j = 0; j < n + 1 - i; j++)
        {
            cout << tab[i][j] << " | ";
        }

    }

    // stosowanie z uogolnionego algorytmu hornera (jestem przekonany co do poprawonoœci kodu w 90% jako ¿e wyniki wydaj¹ siê poprawne ale gdyby tak nie by³o prosi³bym o komentarz gdzie jest b³¹d)
    cout << endl << endl << endl << "podaj wartosci \"z\"" << endl;
    double z;
    cin >> z;

    double wiplus1 = tab[n][0];
    for (int i = n - 1; i >= 1;i--)
    {
        double wi = (wiplus1 * (z - tab[0][i-1])) + tab[i][0];
        wiplus1 = wi;
    }

    // wypisywanie wyniku

    cout << endl << endl << "wartosc w punkce z = " << z << "  wynosi: " << wiplus1 << endl << endl;



}

