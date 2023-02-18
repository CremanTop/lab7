#include <iostream>
#include <cmath>
//#include <time.h>
using namespace std;

const int accuracy = 10000;
const double step = (double)1 / accuracy;

double first_fun(double x);
double second_fun(double x);
double integration(double a, double b, double fun(double));
double integration(double start, double fun1(double), double fun2(double));
double integration(double fun(double));

int main()
{
    //clock_t start = clock();
    double first_point = integration(0, first_fun, second_fun);
    double second_point = integration(abs(first_point) + step * 1.1, first_fun, second_fun);
    double first_integral = integration(first_point, second_point, first_fun);
    double second_integral = integration(first_point, second_point, second_fun);
    cout << abs(first_integral - second_integral) << endl;
    //clock_t end = clock();
    //cout << ((double)end - start) / ((double)CLOCKS_PER_SEC) << endl;
}

double first_fun(double x)
{
    return pow(x, 2) - 8 * x + 16;
}

double second_fun(double x)
{
    return 6 - x;
}

double integration(double a, double b, double fun(double))
{
    const double width = (b - a) / accuracy;

    double result = 0;
    for (int i = 0; i < accuracy; i++)
    {
        double x1 = a + i * width;
        double x2 = a + (i + 1) * width;

        result += 0.5 * (x2 - x1) * (fun(x1) + fun(x2));
    }

    return result;
}

double integration(double start, double fun1(double), double fun2(double))
{
    double i = start;
    while (true)
    {        
        if ((fun1(i) > fun2(i)) != (fun1(i - step) > fun2(i - step))) //Перелом
        {
            return i;
        }
        else if ((fun1(-i) > fun2(-i)) != (fun1(-i + step) > fun2(-i + step)))
        {
            return - i;
        }
        i += step;
    }
}

double integration(double fun(double))
{
    double i = 0;
    double loc_step = step;
    if (fun(step) > fun(-step))
    {
        loc_step = -step;
    }
    while (true)
    {
        if (abs(fun(i)) < abs(fun(i + loc_step)))
        {
            return i;
        }
        i += loc_step;
    }
}