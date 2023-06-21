#include <iostream>

using namespace std;

const int tabsize = 100;

double licz_hi(double ti, double ti1)
{
    return ti1 - ti;
}

double licz_bi(double yi, double yi1, double hi)
{
    return 6 * ((yi1 - yi) / hi);
}

double licz_ui(double hi, double hi_1, double ui_1)
{
    return 2 * (hi + hi_1) - ((hi_1 * hi_1) / ui_1);
}

double licz_vi(double bi, double bi_1, double hi_1, double vi_1, double ui_1)
{
    return (bi - bi_1) - (hi_1 * (vi_1 / ui_1));
}

double licz_zi(double vi, double hi, double zi1, double ui)
{
    return (vi - (hi * zi1)) / ui;
}

double licz_Bi(double hi, double zi, double zi1, double yi, double yi1)
{
    return (-hi / 6) * zi1 - (hi / 3) * zi + (1 / hi) * (yi1 - yi);
}

void licz_Si(double yi, double ti, double Bi, double zi, double hi, double zi1)
{

    // liczenie wspolczynnikow przy wartosciach x do potegi (0,1,2,3)
    pair <double, string> skladowe[4];
    skladowe[0].first = yi + ((ti * ti * zi) / 2) + ((ti * ti * ti * zi) / (6 * hi)) - ((ti * ti * ti * zi1) / (6 * hi)) - (Bi * ti);
    skladowe[0].second = "";

    skladowe[1].first = (Bi)+((ti * ti * zi1) / (2 * hi)) - ((ti * ti * zi) / (2 * hi)) - (ti * zi);
    skladowe[1].second = "x";

    skladowe[2].first = (zi / 2) + ((ti * zi) / (2 * hi)) - ((ti * zi1) / (2 * hi));
    skladowe[2].second = "x^2";

    skladowe[3].first = (zi1 / (6 * hi)) - (zi / (6 * hi));
    skladowe[3].second = "x^3";



    //wypisywanie skladowej Si(x)
    for (int i = 3; i >= 0; i--)
    {
        string znak=" ";
        if (skladowe[i].first > 0 && i<3)
        {
            znak = " +";
        }

        if (skladowe[i].first != 0)
        {
            cout << znak << skladowe[i].first << " " << skladowe[i].second;
        }


    }

}

int main()
{
    int argumenty;
    cout << "Podaj liczbe argumentow:" << endl;
    cin >> argumenty;
    int n = argumenty - 1;
    double arguments[tabsize][2];
    double hi[tabsize];
    double bi[tabsize];
    double ui[tabsize];
    double vi[tabsize];
    double zi[tabsize];
    double Bi[tabsize];
    cout << "Podaj parami punkty i ich wartosci:" << endl;
    for (int i = 0; i <= n;i++)
    {
        cin >> arguments[i][0]; //wczytujemy punkty i ich wartosci
        cin >> arguments[i][1];

    }

    //liczymy hi oraz bi
    for (int i = 0; i <= n-1; i++)
    {
        hi[i] = licz_hi(arguments[i][0], arguments[i + 1][0]);
        bi[i] = licz_bi(arguments[i][1], arguments[i + 1][1], hi[i]);
        cout << endl;
        cout << "h" << i << ":  " << hi[i] << endl;
        cout << "b" << i << ":  " << bi[i] << endl;
    }

    //liczymy ui oraz vi
    ui[1] = 2 * (hi[0] + hi[1]);
    vi[1] = bi[1] - bi[0];
    for (int i = 2; i <= n - 1;i++)
    {
        ui[i] = licz_ui(hi[i], hi[i - 1], ui[i - 1]);
        vi[i] = licz_vi(bi[i], bi[i - 1], hi[i - 1], vi[i - 1], ui[i - 1]);
        cout << endl;
        cout << "u" << i << ":  " << ui[i] << endl;
        cout << "v" << i << ":  " << vi[i] << endl;
    }

    //liczymy zi
    zi[0] = 0;
    zi[n] = 0;
    cout << endl << "z" << n << ": " << zi[n] << endl;
    for (int i = n - 1; i >= 1; i--)
    {
        zi[i] = licz_zi(vi[i], hi[i], zi[i + 1], ui[i]);
        cout << "z" << i << ": " << zi[i] << endl;
    }
    cout << "z0: " << zi[0]  << endl << endl << endl;


    //liczymy Bi
    for (int i = 0;i <= n - 1;i++)
    {
        Bi[i] = licz_Bi(hi[i], zi[i], zi[i + 1], arguments[i][1], arguments[i + 1][1]);
        cout << "B" << i << ":  " << Bi[i] << endl;
    }

    cout << endl << endl;

    //liczymy Si(x)
    for (int i = 0; i <= n - 1;i++)
    {
        cout << "S" << i << "(x) = ";
        licz_Si(arguments[i][1], arguments[i][0], Bi[i], zi[i], hi[i], zi[i + 1]);
        cout << endl;
    }

    cout << endl << endl << endl;

}


