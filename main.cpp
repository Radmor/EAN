#include <iostream>
#include <mpreal.h>
#include <Interval.h>
#include <NumericalPeriodSpline.h>
#include <Exceptions.h>
using namespace std;

int main() {

    NumericalPeriodSpline numericalPeriodSpline;

    int n=6;
    long double x[7]={17,20,23,24,25,27,23.5};
    long double f[7]={4.5,7.0,6.1,5.6,5.8,5.2,4.5};
    long double xx=23.5;

    cout<<numericalPeriodSpline.performValueComputation(n,x,f,xx)<<endl;

    //numericalPeriodSpline.tests();

    return 0;
}