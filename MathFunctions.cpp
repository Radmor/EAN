#include "MathFunctions.h"

long double periodsplinevalue(int n, long double x[],long double f[],long double xx,int st)
{
    int i,k;
    long double v,y,z;
    bool found;
    long double a[4];
    long double u[n+1];
    long double b[n+1],c[n+1],d[n+1];
    long double p[n+1];
    long double q[n+1];


    if(n<1){
        st=1;
    }
    else if(f[0]!=f[n]){
        st=3;
    }
    else if((xx<x[0]) || (xx>x[n])){
        st=4;
    }
    else{
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

        /*
        for(int i=0;i<=n;i++){
            for(k=i+1;i<=n;i++){
                if(x[i]==x[k]){
                    st=2;
                }
            }
        }
         */
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
        return y;
    }
}


long double periodsplinecoeffns(int n, long double x[],long double f[],long double xx,int st){
    long double w,v,y,z,xi;
    long double u[n+1],b[n+1],c[n+1],d[n+1],p[n+1],q[n+1];
    long double a[4][n+1];
}