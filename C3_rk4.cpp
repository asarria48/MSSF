#include <iostream>
#include <cmath>
using namespace std;

double f(double t, double x){
  return x/2;
}

void onesteprk4(double & t, double & x, double dt){

  double dx1 = dt*f(t,x);
  double dx2 = dt*f(t+dt/2, x+dx1/2);
  double dx3 = dt*f(t+dt/2, x+dx2/2);
  double dx4 = dt*f(t+dt, x+dx3);
  
  x += (dx1+2*dx2+2*dx3+dx4)/6;
  t += t*dt;

}

int main(void){
  double t,x;
  double dt = 0.1;

  for(t = 0, x = 1; t < 10;){
    onesteprk4(t,x,dt);
  }

  cout << "x("<<t<<")_approx="<<x<<endl;
  cout << "x("<<t<<")_exacto="<<exp(t/2)<<endl;

  return 0;
}
