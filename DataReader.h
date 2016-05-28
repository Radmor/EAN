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

using namespace std;

class DataReader{
public:
    int n;
    long double x[maxArrayLength];
    long double f[maxArrayLength];
    long double xx;

    int dataread(string pathName);
    void displayOpeningError();



};

#endif //EAN_DATAREADER_H
