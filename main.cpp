#include <iostream>
#include <mpreal.h>
#include <Interval.h>
#include <NumericalPeriodSpline.h>
#include <Exceptions.h>
using namespace std;

int main() {


/*
    int n=6;
    long double x[7]={17,20,23,24,25,27,27.7};
    long double f[7]={4.5,7.0,6.1,5.6,5.8,5.2,4.5};
    long double xx=23.5;
*/

    /*
    int n=1;
    long double x[]={0,1};
    long double f[]={1,1};
    long double xx=0.5;
     */

    int n=2;
    long double x[]={0,1,2};
    long double f[]={1,0,1};
    long double xx=1;



    NumericalPeriodSpline numericalPeriodSpline;
    numericalPeriodSpline.setN(n);

    numericalPeriodSpline.performValueComputation(n,x,f,xx);
    numericalPeriodSpline.performCoeffnsComputation(n,x,f);

    numericalPeriodSpline.displayValue();
    numericalPeriodSpline.displayMatrix();

    //numericalPeriodSpline.tests();

    return 0;
}