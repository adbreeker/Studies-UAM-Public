#include <iostream>
#include <math.h>

using namespace std;

double E = 0.00000001;

double f(double x)
{
    return  exp(x) - 1.5 - atan(x);
}
double pochodna(double x)
{
    return  exp(x) - (1/(1+pow(x,2)));
}

//double pochodna2(double x)
//{
    //return 6*x;
//}

int main()
{
    double a, b, xk1;
    cout << "Podaj przedzial izolacji a b:" << endl;
    cin >> a >> b;

    double xk = a;

    //if (pochodna((a + b) / 2) * pochodna2((a + b) / 2) > 0)
    //{
      //  xk = b;
    //}
    //else
    //{
      //  xk = a;
    //}


    int i = 0;
    do
    {
        i++;
        xk1 = xk - (f(xk) / pochodna(xk));
        cout << "Iteracja " << i << ":  " << xk1;
        xk = xk1;
        cout << endl;
    } while (abs(f(xk1)) > E);

}
