//
// Created by ph on 26.05.16.
//



#ifndef EAN_NUMERICALPERIODSPLINE_H
#define EAN_NUMERICALPERIODSPLINE_H

#define maxArrayLength 1000
#include "mainwindow.h"
#include <QString>

class NumericalPeriodSpline{
private:
    int n;
    long double splineFunctionPointValue;
    long double matrix[4][maxArrayLength];

public:
    void setN(int rowsAmount);
    void performValueComputation(int n, long double x[],long double f[],long double xx);
    void performCoeffnsComputation(int n, long double x[],long double f[]);
    long double periodsplinevalue(int n, long double x[],long double f[],long double xx);
    void periodsplinecoeffns(int n, long double x[],long double f[]);

    long double getValue();
    void displayMatrix(MainWindow* ui);
    void displayMatrixElement(MainWindow *ui,long double element);
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

#endif //EAN_NUMERICALPERIODSPLINE_H
