//
// Created by ph on 27.05.16.
//

#ifndef EAN_EXCEPTIONS_H
#define EAN_EXCEPTIONS_H

#include <exception>
using namespace std;


class TooFewNodesException: public exception{
public:
    const char * what() const throw(){
        return "Too few nodes of interpolation!";
    }
};

class SameNodesValue: public exception{
public:

    const char * what() const throw(){
        return "Two different nodes have the same value!";
    }
};

class FirstandLastNodeInterpolValueNotSame: public exception{
public:
    const char * what() const throw(){
        return "First and last interpolated function node value is not the same!";
    }
};

class PointValueInvalid: public exception{
public:
    const char * what() const throw(){
        return "Point value less than first node value or greater than last node value!";
    }
};


#endif //EAN_EXCEPTIONS_H
