//
// Created by ph on 26.05.16.
//

#include "NumericalPeriodSpline.h"
#include <stdio.h>
#include <Exceptions.h>
#include <Utilities.h>

#define matrixColumnsAmount 4

long double NumericalPeriodSpline::getValue() {
    return this->splineFunctionPointValue;
}

void NumericalPeriodSpline::setN(int rowsAmount) {
    this->n=rowsAmount;
}


void NumericalPeriodSpline::displayMatrixElement(MainWindow* ui,long double element) {

    QString tekst;

    char intervalElementString[100];
    sprintf(intervalElementString,"%.21LE\t",element);

    ui->displayMatrixElement(tekst.fromStdString(intervalElementString));

}

void NumericalPeriodSpline::displayNewLine(MainWindow* ui){
    QString tekst;
    ui->displayMatrixElement(tekst.fromStdString("\n"));
}


void NumericalPeriodSpline::displayMatrix(MainWindow* ui){
    ui->clearMatrixTextBrowser();
    for(int j=0;j<matrixColumnsAmount;j++){
        for(int i=0;i<n;i++){
            this->displayMatrixElement(ui,this->matrix[j][i]);
        }
        this->displayNewLine(ui);
    }
}


void NumericalPeriodSpline::displayValue(MainWindow* ui){

    QString tekst;

    char valueString[100];
    sprintf(valueString,"%.21LE",this->splineFunctionPointValue);

    ui->displayValue(tekst.fromStdString(valueString));

}

/*
void NumericalPeriodSpline::displayMatrix(){
    printf("\n\n");
    for(int j=0;j<matrixColumnsAmount;j++){
        for(int i=0;i<n;i++){
            printf("%.21LE ",this->matrix[j][i]);
        }
        printf("\n");
    }
}


void NumericalPeriodSpline::displayValue(){
    printf("%.21LE",this->splineFunctionPointValue);
}

void NumericalPeriodSpline::setN(int rowsAmount) {

    this->n=rowsAmount;
}

*/
void NumericalPeriodSpline::performValueComputation(int n, long double x[],long double f[],long double xx){

    try{
        this->periodsplinevalue(n,x,f,xx);
    }
    catch(exception &e){
        displayException(e.what());
    }

}

void NumericalPeriodSpline::performCoeffnsComputation(int n, long double x[],long double f[]){

    try{
        this->periodsplinecoeffns(n,x,f);
    }
    catch(exception &e){
        displayException(e.what());
    }
}

long double NumericalPeriodSpline::periodsplinevalue(int n, long double x[],long double f[],long double xx) {

    int i,k;
    long double v,y,z;
    bool found;
    long double a[4];
    long double u[n+1];
    long double b[n+1],c[n+1],d[n+1];
    long double p[n+1];
    long double q[n+1];
    int st=0;


    if(n<1){
        st=1;
        throw TooFewNodesException();
    }
    else if(f[0]!=f[n]){
        st=3;
        throw FirstandLastNodeInterpolValueNotSame();
    }
    else if((xx<x[0]) || (xx>x[n])){
        st=4;
        throw PointValueInvalid();
    }
    else{
        /*
        st=0;
        i=-1;

        do{
            i=i+1;
            for(k=i+1;k<=n;k++){
                if(x[i]==x[k]){
                    st=2;
                }
            }
        }while((i!=n-1) && (st!=2));
         */

        for(int i=0;i<=n;i++){
            for(k=i+1;k<=n;k++){
                if(x[i]==x[k]){
                    st=2;
                    throw SameNodesValue();
                }
            }
        }

    }

    if (st==0) {
        if(n>1){
            v=x[1]-x[0];
            z=x[n]-x[n-1];
            b[n]=v/(z+v);
            c[n]=1-b[n];
            y=f[n];
            d[n]=6*((f[1]-y)/v-(y-f[n-1])/z)/(z+v);
            for(i=1;i<=n-1;i++){
                z=x[i];
                y=x[i+1]-z;
                z=z-x[i-1];
                v=f[i];
                b[i]=y/(y+z);
                c[i]=1-b[i];
                d[i]=6*((f[i+1]-v)/y-(v-f[i-1])/z)/(y+z);
            }
            if(n>2){
                u[1]=2;
                c[2]=c[2]/2;
                q[2]=-b[n]/2;
                for(i=2;i<=n-2;i++){
                    v=2-b[i-1]*c[i];
                    c[i+1]=c[i+1]/v;
                    q[i+1]=-q[i]*b[i-1]/v;
                    u[i]=v;
                }
                v=2-c[n-1]*b[n-2];
                q[n]=(c[n]-q[n-1]*b[n-2])/v;
                u[n-1]=v;
                p[1]=c[1];
                for(i=2;i<=n-2;i++)
                    p[i]=-c[i]*p[i-1];

                p[n-1]=b[n-1]-c[n-1]*p[n-2];
                v=2-c[1]*p[2];

                for(i=2;i<=n-2;i++)
                    v=v-p[i]*p[i+1];

                u[n]=v-p[n-1]*q[n];

                for(i=2;i<=n-1;i++)
                    d[i]=d[i]-c[i]*d[i-1];

                v=d[n];

                for(i=2;i<=n;i++)
                    v=v-q[i]*d[i-1];

                d[n]=v;
                u[n]=d[n]/u[n];
                u[n-1]=(d[n-1]-p[n-1]*u[n])/u[n-1];

                for(i=n-2;i>=1;i--)
                    u[i]=(d[i]-b[i]*u[i+1]-p[i]*u[n])/u[i];
            }
            else{
                y=d[1];
                z=d[2];
                v=4-c[2]*b[1];
                u[1]=(2*y-b[1]*z)/v;
                u[2]=(2*z-c[2]*y)/v;
            }

        }
        else
            u[1]=0;

        u[0]=u[n];

        /* BEGIN OF COEFFNS CALC */
        /*


        long double w,xi;
        long double z1,y1,v1;

        for(int i=0;i<=n-1;i++) {

            w = f[i];
            xi = x[i];
            z1 = x[i + 1] - xi;

            y1 = u[i];
            v1 = (f[i + 1] - w) / z1 - (2 * y1 + u[i + 1]) * z1 / 6;
            z1 = (u[i + 1] - y1) / (6 * z1);
            y1 = y1 / 2;
            this->matrix[i][0] = ((-z1 * xi + y1) * xi - v1) * xi + w;
            w = 3 * z1 * xi;
            this->matrix[i][1] = (w - 2 * y1) * xi + v1;
            this->matrix[i][2] = y1 - w;
            this->matrix[i][3] = z1;

        }

        */




        /* END OF COEFFNS CALC */


        found=false;
        i=-1;
        do{
            i=i+1;
            if ((xx>=x[i]) && (xx<=x[i+1])){
                found=true;
            }

        }while(!found);





        y=x[i+1]-x[i];
        z=u[i+1];
        v=u[i];
        a[0]=f[i];
        a[1]=(f[i+1]-f[i])/y-(2*v+z)*y/6;
        a[2]=v/2;
        a[3]=(z-v)/(6*y);
        y=a[3];
        z=xx-x[i];
        for(i=2;i>=0;i--)
            y=y*z+a[i];
        this->splineFunctionPointValue=y;
        return y;
    }
}


void NumericalPeriodSpline::periodsplinecoeffns(int n, long double *x, long double *f) {

        int i,k;
        long double v,y,z;
        bool found;
        long double a[4];
        long double u[n+1];
        long double b[n+1],c[n+1],d[n+1];
        long double p[n+1];
        long double q[n+1];
        int st=0;


        if(n<1){
            st=1;
            throw TooFewNodesException();
        }
        else if(f[0]!=f[n]){
            st=3;
            throw FirstandLastNodeInterpolValueNotSame();
        }
        else{
            for(int i=0;i<=n;i++){
                for(k=i+1;k<=n;k++){
                    if(x[i]==x[k]){
                        st=2;
                        throw SameNodesValue();
                    }
                }
            }

        }

        if (st==0) {
            if(n>1){
                v=x[1]-x[0];
                z=x[n]-x[n-1];
                b[n]=v/(z+v);
                c[n]=1-b[n];
                y=f[n];
                d[n]=6*((f[1]-y)/v-(y-f[n-1])/z)/(z+v);
                for(i=1;i<=n-1;i++){
                    z=x[i];
                    y=x[i+1]-z;
                    z=z-x[i-1];
                    v=f[i];
                    b[i]=y/(y+z);
                    c[i]=1-b[i];
                    d[i]=6*((f[i+1]-v)/y-(v-f[i-1])/z)/(y+z);
                }
                if(n>2){
                    u[1]=2;
                    c[2]=c[2]/2;
                    q[2]=-b[n]/2;
                    for(i=2;i<=n-2;i++){
                        v=2-b[i-1]*c[i];
                        c[i+1]=c[i+1]/v;
                        q[i+1]=-q[i]*b[i-1]/v;
                        u[i]=v;
                    }
                    v=2-c[n-1]*b[n-2];
                    q[n]=(c[n]-q[n-1]*b[n-2])/v;
                    u[n-1]=v;
                    p[1]=c[1];
                    for(i=2;i<=n-2;i++)
                        p[i]=-c[i]*p[i-1];

                    p[n-1]=b[n-1]-c[n-1]*p[n-2];
                    v=2-c[1]*p[2];

                    for(i=2;i<=n-2;i++)
                        v=v-p[i]*p[i+1];

                    u[n]=v-p[n-1]*q[n];

                    for(i=2;i<=n-1;i++)
                        d[i]=d[i]-c[i]*d[i-1];

                    v=d[n];

                    for(i=2;i<=n;i++)
                        v=v-q[i]*d[i-1];

                    d[n]=v;
                    u[n]=d[n]/u[n];
                    u[n-1]=(d[n-1]-p[n-1]*u[n])/u[n-1];

                    for(i=n-2;i>=1;i--)
                        u[i]=(d[i]-b[i]*u[i+1]-p[i]*u[n])/u[i];
                }
                else{
                    y=d[1];
                    z=d[2];
                    v=4-c[2]*b[1];
                    u[1]=(2*y-b[1]*z)/v;
                    u[2]=(2*z-c[2]*y)/v;
                }

            }
            else
                u[1]=0;

            u[0]=u[n];

            /* BEGIN OF COEFFNS CALC */


            long double w,xi;
            long double z1,y1,v1;

            for(int i=0;i<=n-1;i++) {

                w = f[i];
                xi = x[i];
                z1 = x[i + 1] - xi;

                y1 = u[i];
                v1 = (f[i + 1] - w) / z1 - (2 * y1 + u[i + 1]) * z1 / 6;
                z1 = (u[i + 1] - y1) / (6 * z1);
                y1 = y1 / 2;
                this->matrix[0][i] = ((-z1 * xi + y1) * xi - v1) * xi + w;
                w = 3 * z1 * xi;
                this->matrix[1][i] = (w - 2 * y1) * xi + v1;
                this->matrix[2][i] = y1 - w;
                this->matrix[3][i] = z1;

            }
            /* END OF COEFFNS CALC */
        }

}

void NumericalPeriodSpline::tests(){
    test1();
    //test2();
    //test3();



}
void NumericalPeriodSpline::test1(){

    NumericalPeriodSpline numericalPeriodSpline;
    int n=6;
    long double x[7]={17,20,23,24,25,27,27.7};
    long double f[7]={4.5,7.0,6.1,5.6,5.8,5.2,4.5};
    long double xx=23.5;
    long double correctvalue=5.78370874774388E+0000;
    numericalPeriodSpline.performValueComputation(n,x,f,xx);

    printf("TEST 1\n");
    printf("Wartosc funkcji: %.21LE \npowinno być      %.21LE \n\n",this->getValue(),correctvalue);
}
/*
void NumericalPeriodSpline::test2(){
    int n=1;
    long double x[]={0,1};
    long double f[]={1,1};
    long double xx=0.5;
    int st=0;
    long double correctvalue=1.00000000000000E+0000;
    printf("TEST 2\n");
    printf("Wartosc funkcji: %.21LE \npowinno być      %.21LE \n\n",periodsplinevalue(n,x,f,xx,st),correctvalue);
}void NumericalPeriodSpline::test3() {
    int n=2;
    long double x[]={0,1,2};
    long double f[]={1,0,1};
    long double xx=1;
    int st=0;
    long double correctvalue = 5.42101086242752E-0020;
    printf("TEST 3\n");
    printf("Wartosc funkcji: %.21LE \npowinno być      %.21LE \n\n", periodsplinevalue(n, x, f, xx, st), correctvalue);
}
void NumericalPeriodSpline::test4(){
    int n=2;
    long double x[]={0,1,2};
    long double f[]={1,0,1};
    long double xx=3;
    int st=0;
    long double correctvalue;
    printf("TEST 3\n");
    printf("Wartosc funkcji: %.21LE \npowinno być      %.21LE \n\n", periodsplinevalue(n, x, f, xx, st), correctvalue);
}
*/
