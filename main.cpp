#include <cstddef>
#include <iostream>
#include <mpreal.h>
#include <Interval.h>
#include <NumericalPeriodSpline.h>
#include <IntervalPeriodSpline.h>
#include <DataReader.h>
#include <Utilities.h>

using namespace std;

int main() {

    DataReader dataReader;
    NumericalPeriodSpline numericalPeriodSpline;
    IntervalPeriodSpline intervalPeriodSpline;


    try{
        dataReader.dataread("/home/ph/Dokumenty/EAN/data3.txt");



        numericalPeriodSpline.setN(dataReader.n);
        numericalPeriodSpline.performValueComputation(dataReader.n,dataReader.xLD,dataReader.fLD,dataReader.xxLD);
        numericalPeriodSpline.performCoeffnsComputation(dataReader.n,dataReader.xLD,dataReader.fLD);
        numericalPeriodSpline.displayValue();
        numericalPeriodSpline.displayMatrix();



        intervalPeriodSpline.setN(dataReader.n);
        intervalPeriodSpline.performValueComputation(dataReader.n,dataReader.xINT,dataReader.fINT,dataReader.xxINT);
        intervalPeriodSpline.performCoeffnsComputation(dataReader.n,dataReader.xINT,dataReader.fINT);
        intervalPeriodSpline.displayValue();
        intervalPeriodSpline.displayMatrix();


    }
    catch(exception &e){
        displayException(e.what());
    }




/*
    NumericalPeriodSpline numericalPeriodSpline;
    numericalPeriodSpline.setN(n);

    numericalPeriodSpline.performValueComputation(n,x,f,xx);
    numericalPeriodSpline.performCoeffnsComputation(n,x,f);

    numericalPeriodSpline.displayValue();
    numericalPeriodSpline.displayMatrix();

    //numericalPeriodSpline.tests();
    */

    return 0;
}