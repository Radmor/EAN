#include <iostream>
#include <mpreal.h>
#include <Interval.h>
#include <MathFunctions.h>
using namespace std;

int main() {


    int n=6;
    long double x[7]={17,20,23,24,25,27,27.7};
    long double f[7]={4.5,7.0,6.1,5.6,5.8,5.2,4.5};
    long double xx=23.5;
    int st=0;

    /*
    int n=2;
    long double x[7]={0,1,2};
    long double f[7]={1,0,1};
    long double xx=1;
    int st=0;
     */

    /*
    int n=2;
    long double x[7]={0,1,2};
    long double f[7]={1,0,1};
    long double xx=3;
    int st=0;
    */


    cout<<periodsplinevalue(n,x,f,xx,st);

    return 0;
}