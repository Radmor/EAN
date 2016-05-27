//
// Created by ph on 26.05.16.
//

#ifndef EAN_NUMERICALPERIODSPLINE_H
#define EAN_NUMERICALPERIODSPLINE_H

class NumericalPeriodSpline{
private:

public:
    long double performValueComputation(int n, long double x[],long double f[],long double xx);
    long double periodsplinevalue(int n, long double x[],long double f[],long double xx);
    void tests();
    void test1();
    /*
     * void test2();
    void test3();
    void test4();
     */


};

#endif //EAN_NUMERICALPERIODSPLINE_H
