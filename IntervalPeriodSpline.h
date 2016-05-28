//
// Created by ph on 28.05.16.
//

#ifndef EAN_INTERVALPERIODSPLINE_H
#define EAN_INTERVALPERIODSPLINE_H

#define maxArrayLength 1000
#define matrixColumnsAmount 4

#include <cstddef>
#include <mpreal.h>
#include <Interval.h>
#include <Utilities.h>
#include <Exceptions.h>
#include "mainwindow.h"


using namespace interval_arithmetic;

class IntervalPeriodSpline{
private:
    int n;
    Interval<long double> splineFunctionPointValue;
    Interval<long double> matrix[matrixColumnsAmount][maxArrayLength];

public:
    void setN(int rowsAmount);
    void performValueComputation(int n, Interval<long double> x[],Interval<long double> f[],Interval<long double> xx);
    void performCoeffnsComputation(int n, Interval<long double> x[],Interval<long double> f[]);
    void periodsplinevalue(int n, Interval<long double> x[],Interval<long double> f[],Interval<long double> xx);
    void periodsplinecoeffns(int n, Interval<long double> x[],Interval<long double> f[]);

    void displayIntervalElement(MainWindow* ui,Interval<long double> interval);

    Interval<long double> getValue();
    void displayMatrix(MainWindow* ui);
    void displayValue(MainWindow* ui);
    void displayNewLine(MainWindow* ui);
    void tests();
    void test1();
    /*
     * void test2();
    void test3();
    void test4();
     */


};


#endif //EAN_INTERVALPERIODSPLINE_H
