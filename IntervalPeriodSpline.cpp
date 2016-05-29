//
// Created by ph on 28.05.16.
//

#include "IntervalPeriodSpline.h"

#include "mainwindow.h"

/*
bool operator<(Interval a,Interval b){
    return a.a<b.a && a.b<b.b;
}
 */

bool operator==(Interval<long double> a,Interval<long double> b){
    return (a.a==b.a && a.b==b.b);
}

bool operator!=(Interval<long double> a,Interval<long double> b){
    return (a.a!=b.a || a.b!=b.b);
}

bool operator>(Interval<long double> a,Interval<long double> b){
    return (a.a>b.a && a.b>b.b);
}

bool operator>=(Interval<long double> a,Interval<long double> b){
    return (a.a>=b.a && a.b>=b.b);
}

bool operator<=(Interval<long double> a,Interval<long double> b){
    return (a.a<=b.a && a.b<=b.b);
}

bool operator<(Interval<long double> a,Interval<long double> b){
    return (a.a<b.a && a.b<b.b);
}

Interval<long double> IntervalPeriodSpline::getValue() {
    return this->splineFunctionPointValue;
}

void IntervalPeriodSpline::displayIntervalElement(MainWindow* ui,Interval<long double> interval) {

    QString tekst;

    char intervalElementString[100];
    sprintf(intervalElementString,"[%.21LE, %.21LE]\t",interval.a,interval.b);

    ui->displayMatrixElement(tekst.fromStdString(intervalElementString));

}

void IntervalPeriodSpline::displayNewLine(MainWindow* ui){
    QString tekst;
    ui->displayMatrixElement(tekst.fromStdString("\n"));
}


void IntervalPeriodSpline::displayMatrix(MainWindow* ui){
    ui->clearMatrixTextBrowser();
    for(int j=0;j<matrixColumnsAmount;j++){
        for(int i=0;i<n;i++){
            this->displayIntervalElement(ui,this->matrix[j][i]);
        }
        this->displayNewLine(ui);
    }
}


void IntervalPeriodSpline::displayValue(MainWindow* ui){

    QString tekst;

    char valueString[100];
    sprintf(valueString,"[%.21LE, %.21LE]",this->splineFunctionPointValue.a,this->splineFunctionPointValue.b);

    ui->displayValue(tekst.fromStdString(valueString));

}

void IntervalPeriodSpline::setN(int rowsAmount) {

    this->n=rowsAmount;
}


void IntervalPeriodSpline::performValueComputation(int n, Interval<long double> x[],Interval<long double> f[],Interval<long double> xx){


    try{
        this->periodsplinevalue(n,x,f,xx);
    }
    catch(exception &e){
        displayException(e.what());
    }

}

void IntervalPeriodSpline::performCoeffnsComputation(int n, Interval<long double> x[],Interval<long double> f[]){

    try{
        this->periodsplinecoeffns(n,x,f);
    }
    catch(exception &e){
        displayException(e.what());
    }
}

void IntervalPeriodSpline::periodsplinevalue(int n, Interval<long double> x[],Interval<long double> f[],Interval<long double> xx) {

    int i,k;
    Interval<long double> v,y,z;
    bool found;
    Interval<long double> a[4];
    Interval<long double> u[n+1];
    Interval<long double> b[n+1],c[n+1],d[n+1];
    Interval<long double> p[n+1];
    Interval<long double> q[n+1];
    int st=0;




    if(n<1){
        st=1;
        throw TooFewNodesException();
    }
    else if(f[0]!=f[n]){
        st=3;
        throw FirstandLastNodeInterpolValueNotSame();
    }
    else if(xx<x[0] || xx>x[n]){
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
                    //this->displayIntervalElement(f[0]);
                    //this->displayIntervalElement(f[n]);
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
            c[n]=Interval<long double>(1,1)-b[n];
            y=f[n];
            d[n]=Interval<long double>(6,6)*((f[1]-y)/v-(y-f[n-1])/z)/(z+v);
            for(i=1;i<=n-1;i++){
                z=x[i];
                y=x[i+1]-z;
                z=z-x[i-1];
                v=f[i];
                b[i]=y/(y+z);
                c[i]=Interval<long double>(1,1)-b[i];
                d[i]=Interval<long double>(6,6)*((f[i+1]-v)/y-(v-f[i-1])/z)/(y+z);
            }
            if(n>2){
                u[1]=Interval<long double>(2,2);
                c[2]=c[2]/Interval<long double>(2,2);
                q[2]=Interval<long double>(-1,-1)*b[n]/Interval<long double>(2,2);
                for(i=2;i<=n-2;i++){
                    v=Interval<long double>(2,2)-b[i-1]*c[i];
                    c[i+1]=c[i+1]/v;
                    q[i+1]=Interval<long double>(-1,-1)*q[i]*b[i-1]/v;
                    u[i]=v;
                }
                v=Interval<long double>(2,2)-c[n-1]*b[n-2];
                q[n]=(c[n]-q[n-1]*b[n-2])/v;
                u[n-1]=v;
                p[1]=c[1];
                for(i=2;i<=n-2;i++)
                    p[i]=Interval<long double>(-1,-1)*c[i]*p[i-1];

                p[n-1]=b[n-1]-c[n-1]*p[n-2];
                v=Interval<long double>(2,2)-c[1]*p[2];

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
                v=Interval<long double>(4,4)-c[2]*b[1];
                u[1]=(Interval<long double>(2,2)*y-b[1]*z)/v;
                u[2]=(Interval<long double>(2,2)*z-c[2]*y)/v;
            }

        }
        else
            u[1]=Interval<long double>(0,0);

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


        /*found=false;
        i=-1;
        do{
            i=i+1;
            if ((xx.a>x[i].a && xx.b>x[i].b) || (xx.a<x[n].a && xx.b<x[n].b)){
                found=true;
            }

        }while(!found);
         */


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
        a[1]=(f[i+1]-f[i])/y-(Interval<long double>(2,2)*v+z)*y/Interval<long double>(6,6);
        a[2]=v/Interval<long double>(2,2);
        a[3]=(z-v)/(Interval<long double>(6,6)*y);
        y=a[3];
        z=xx-x[i];
        for(i=2;i>=0;i--)
            y=y*z+a[i];
        this->splineFunctionPointValue=y;
    }
}

void IntervalPeriodSpline::periodsplinecoeffns(int n, Interval<long double> x[],Interval<long double> f[]) {

    int i,k;
    Interval<long double> v,y,z;
    bool found;
    Interval<long double> a[4];
    Interval<long double> u[n+1];
    Interval<long double> b[n+1],c[n+1],d[n+1];
    Interval<long double> p[n+1];
    Interval<long double> q[n+1];
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
            c[n]=Interval<long double>(1,1)-b[n];
            y=f[n];
            d[n]=Interval<long double>(6,6)*((f[1]-y)/v-(y-f[n-1])/z)/(z+v);
            for(i=1;i<=n-1;i++){
                z=x[i];
                y=x[i+1]-z;
                z=z-x[i-1];
                v=f[i];
                b[i]=y/(y+z);
                c[i]=Interval<long double>(1,1)-b[i];
                d[i]=Interval<long double>(6,6)*((f[i+1]-v)/y-(v-f[i-1])/z)/(y+z);
            }
            if(n>2){
                u[1]=Interval<long double>(2,2);
                c[2]=c[2]/Interval<long double>(2,2);
                q[2]=Interval<long double>(-1,-1)*b[n]/Interval<long double>(2,2);
                for(i=2;i<=n-2;i++){
                    v=Interval<long double>(2,2)-b[i-1]*c[i];
                    c[i+1]=c[i+1]/v;
                    q[i+1]=Interval<long double>(-1,-1)*q[i]*b[i-1]/v;
                    u[i]=v;
                }
                v=Interval<long double>(2,2)-c[n-1]*b[n-2];
                q[n]=(c[n]-q[n-1]*b[n-2])/v;
                u[n-1]=v;
                p[1]=c[1];
                for(i=2;i<=n-2;i++)
                    p[i]=Interval<long double>(-1,-1)*c[i]*p[i-1];

                p[n-1]=b[n-1]-c[n-1]*p[n-2];
                v=Interval<long double>(2,2)-c[1]*p[2];

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
                v=Interval<long double>(4,4)-c[2]*b[1];
                u[1]=(Interval<long double>(2,2)*y-b[1]*z)/v;
                u[2]=(Interval<long double>(2,2)*z-c[2]*y)/v;
            }

        }
        else
            u[1]=Interval<long double>(0,0);

        u[0]=u[n];




        Interval<long double> w,xi;
        Interval<long double> z1,y1,v1;

        for(int i=0;i<=n-1;i++) {

            w = f[i];
            xi = x[i];
            z1 = x[i + 1] - xi;

            y1 = u[i];
            v1 = (f[i + 1] - w) / z1 - (Interval<long double>(2,2) * y1 + u[i + 1]) * z1 / Interval<long double>(6,6);
            z1 = (u[i + 1] - y1) / (Interval<long double>(6,6) * z1);
            y1 = y1 / Interval<long double>(2,2);
            this->matrix[0][i] = ((Interval<long double>(-1,-1)*z1 * xi + y1) * xi - v1) * xi + w;
            w = Interval<long double>(3,3) * z1 * xi;
            this->matrix[1][i] = (w - Interval<long double>(2,2) * y1) * xi + v1;
            this->matrix[2][i] = y1 - w;
            this->matrix[3][i] = z1;

       }
    }

}

