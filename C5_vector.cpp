#include <iostream>
#include <cmath>
#include "vector.h"
using namespace std;


const double g = 9.8;

class object;    //declarar clase

class object{    //declarar interfaz
private:
  vector3D r,V,F; double m,R;
public:
  void start(double x0, double y0, double z0, double Vx0, double Vy0, double Vz0, double m0, double R0);
  void calcf(void);
  void move(double dt);
  double getx(void){return r.x();};
  double gety(void){return r.y();};
};


void object::start(double x0, double y0, double z0, double Vx0, double Vy0,double Vz0, double m0, double R0){    //implementación de las funciones 
  r.load(x0,y0,z0);
  V.load(Vx0,Vy0,Vz0);
  m = m0;
  R= R0;
}
void object::calcf(void){
  F.load(0,-m*g,0);
}
void object::move(double dt){
  r+=V*dt;
  V+=F*(dt/m);
}
  
int main(){
  double t,dt = 0.001;
  double ttot = 2.5;
  int ncuadros = 200; double tdraw, tcuad = ttot/ncuadros;
  object ball;

  ball.start(0,0, 0,16,9, 0, 0.453,1.0);
  for(t=tdraw=0;t<ttot;t+=dt,tdraw+=dt){
    if(tdraw>tcuad){

      tdraw=0;
    }
    cout << ball.getx()<< " " << ball.gety() << endl;
  ball.calcf();
  ball.move(dt);
  }
  
  return 0;
}

