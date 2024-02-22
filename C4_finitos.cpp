#include <iostream>
#include <cmath>
using namespace std;

const double g = 9.8;

class object;    //declarar clase

class object{    //declarar interfaz
private:
  double x,y,vx,vy,fx,fy,m,r;
public:
  void start(double x0, double y0, double vx0, double vy0, double m0, double r0);
  void calcf(void);
  void move(double dt);
  double getx(void){return x;};
  double gety(void){return y;};
};


void object::start(double x0, double y0, double vx0, double vy0, double m0, double r0){    //implementación de las funciones 
  x = x0;
  y = y0;
  vx = vx0;
  vy = vy0;
  m = m0;
  r = r0;
}
void object::calcf(void){
  fx = 0;
  fy = -m*g;
}
void object::move(double dt){
  x += vx*dt;
  y += vy*dt;
  vx += fx*dt/m;
  vy += fy*dt/m;
}
  
int main(){
  double t,dt = 0.1;
  object ball;

  ball.start(0,0,16,9,0.453,0.11);
  for(t=0;t<2.5;t+=dt){
    cout << ball.getx()<< " " << ball.gety() << endl;
  ball.calcf();
  ball.move(dt);
  }
  
  return 0;
}
