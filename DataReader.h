//
// Created by ph on 27.05.16.
//

#ifndef EAN_DATAREADER_H
#define EAN_DATAREADER_H

#define maxArrayLength 1000

#include <string>
#include <fstream>
#include <iostream>
#include <boost/regex.hpp>
#include <regex>

#include <cstddef>
#include <mpreal.h>
#include <Interval.h>

using namespace std;
using namespace interval_arithmetic;

class DataReader{
public:
    int n;
    long double xLD[maxArrayLength];
    long double fLD[maxArrayLength];
    long double xxLD;

    Interval<long double> xINT[maxArrayLength];
    Interval<long double> fINT[maxArrayLength];
    Interval<long double> xxINT;

    int dataread(string pathName);
    void displayOpeningError();



};

#endif //EAN_DATAREADER_H
