#include <iostream>
#include <cmath>
using namespace std;

double f(double t, double x, double n){
    return cos(n*t - x*sin(t));
}

double simpson(double a, double b, int nsteps, double x, double n){
    nsteps *= 2;
    double dx = (b-a)/nsteps;
    double sum = 0;

    for(int i = 0; i < nsteps + 1; i++){
        double t = a + i*dx;
        if(i==0 || i==nsteps){
            sum += f(t,x,n);
        }
        else if(i%2 == 0){
            sum += 2*f(t,x,n);
        }
        else{
            sum += 4*f(t,x,n);
        }
    }
    return sum*dx/3;
    }

double bessel(double n, double x){
    return (1/M_PI)*simpson(0,M_PI,100,x,n);
}

int main(){

    double n = 0;
    double a = 0;
    double b = 10;
    double nsteps = 100;
    double dx = (b-a)/nsteps;

    for(int i = 0; i < nsteps; i++){
        double x = a + i*dx;

        cout << x << " " << bessel(n,x) <<endl;
    }

    return 0;
}