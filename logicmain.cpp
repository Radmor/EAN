#include <cstddef>
#include <iostream>
#include <mpreal.h>
#include <Interval.h>
#include <NumericalPeriodSpline.h>
#include <IntervalPeriodSpline.h>
#include <DataReader.h>
#include <logicmain.h>

using namespace std;

void logicfunction(MainWindow* ui,string filepath,bool ifNumeric){
    DataReader dataReader;
    NumericalPeriodSpline numericalPeriodSpline;
    IntervalPeriodSpline intervalPeriodSpline;

    //filepath="/home/ph/Dokumenty/EAN/data3.txt";

    try{
        dataReader.dataread(filepath);

        if(ifNumeric){
            numericalPeriodSpline.setN(dataReader.n);
            numericalPeriodSpline.periodsplinecoeffns(dataReader.n,dataReader.xLD,dataReader.fLD);
            numericalPeriodSpline.displayMatrix(ui);
            numericalPeriodSpline.periodsplinevalue(dataReader.n,dataReader.xLD,dataReader.fLD,dataReader.xxLD);
            numericalPeriodSpline.displayValue(ui);

        }
        else{
            intervalPeriodSpline.setN(dataReader.n);
            intervalPeriodSpline.periodsplinecoeffns(dataReader.n,dataReader.xINT,dataReader.fINT);
            intervalPeriodSpline.displayMatrix(ui);
            intervalPeriodSpline.periodsplinevalue(dataReader.n,dataReader.xINT,dataReader.fINT,dataReader.xxINT);
            intervalPeriodSpline.displayValue(ui);

        }
    }
    catch (PointValueInvalid &e){
        QString tekst;
        ui->displayValue(tekst.fromStdString("Function value cannot be computed in this point"));
    }
    catch(exception &e){
        QString tekst;
        ui->displayException(tekst.fromStdString(e.what()));
    }


}
/*
int main() {
    logicfunction();
    return 0;
}
*/
