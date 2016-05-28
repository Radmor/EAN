#include <cstddef>
#include <iostream>
#include <mpreal.h>
#include <Interval.h>
#include <NumericalPeriodSpline.h>
#include <DataReader.h>
#include <Utilities.h>

using namespace std;

int main() {

    DataReader dataReader;
    NumericalPeriodSpline numericalPeriodSpline;

    try{
        dataReader.dataread("/home/ph/Dokumenty/EAN/data4.txt");

        numericalPeriodSpline.setN(dataReader.n);
        numericalPeriodSpline.performValueComputation(dataReader.n,dataReader.x,dataReader.f,dataReader.xx);
        numericalPeriodSpline.performCoeffnsComputation(dataReader.n,dataReader.x,dataReader.f);

        numericalPeriodSpline.displayValue();
        numericalPeriodSpline.displayMatrix();
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