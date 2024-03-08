#include <iostream>
#include <cmath>
#include "vector.h"
#include "Random64.h"
using namespace std;

//Constantes del problema físico
const int Nx = 5, Ny = 5;
const int N = Nx*Ny;
const double G = 1.0;
const double Khertz = 1.0e4;
double Lx = 60, Ly = 60;

//Constantes del algoritmo de integración
const double xi=0.1786178958448091;
const double lambda=-0.2123418310626054;
const double chi=-0.06626458266981849;
const double Um2lambdau2=(1-2*lambda)/2;
const double Um2chiplusxi=1-2*(chi+xi);

//--------------- Declarar las clases-----------
class Cuerpo;
class Colisionador;

//--------- Declarar las interfases de las clases---------
class Cuerpo{
private:
  vector3D r,V,F; double m,R;
public:
  void Inicie(double x0,double y0,double z0,
	      double Vx0,double Vy0,double Vz0,double m0,double R0);
  void BorreFuerza(void){F.load(0,0,0);};// Inline
  void SumeFuerza(vector3D dF){F+=dF;};// Inline
  void Mueva_r(double dt,double coeficiente);
  void Mueva_V(double dt,double coeficiente);
  void Dibujese(void);
  double Getx(void){return r.x();}; // Inline
  double Gety(void){return r.y();}; // Inline
  friend class Colisionador;
};
class Colisionador{
private:
public:
  void CalculeTodasLasFuerzas(Cuerpo * Planetas);
  void CalculeFuerzaEntre(Cuerpo & Planeta1,Cuerpo & Planeta2);
};

//-------Implementar las funciones de las clases------
//------- Funciones de la clase cuerpo --------
void Cuerpo::Inicie(double x0,double y0,double z0,
	      double Vx0,double Vy0,double Vz0,double m0,double R0){
  r.load(x0,y0,z0);  V.load(Vx0,Vy0,Vz0); m=m0; R=R0;
}
void Cuerpo::Mueva_r(double dt,double coeficiente){
  r+=V*(coeficiente*dt);
}
void Cuerpo::Mueva_V(double dt,double coeficiente){
  V+=F*(coeficiente*dt/m);
}

void Cuerpo::Dibujese(void){
  cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)";
}

//------- Funciones de la clase Colisionador --------
void Colisionador::CalculeTodasLasFuerzas(Cuerpo * Planeta){
  int i,j;
  //Borro las fuerzas de todos los planetas
  for(i=0;i<N+4;i++)
    Planeta[i]. BorreFuerza();
  //Recorro por parejas, calculo la fuerza de cada pareja y se la sumo a los dos
  for(i=0;i<N;i++){
    for(j=i+1;j<N+4;j++){
      CalculeFuerzaEntre(Planeta[i],Planeta[j]);}
  }
}
void Colisionador::CalculeFuerzaEntre(Cuerpo & Planeta1,Cuerpo & Planeta2){
  //determinar si hay colisión
  vector3D r21=Planeta2.r-Planeta1.r; double d=r21.norm2();
  double R1 = Planeta1.R, R2 = Planeta2.R;
  double s = (R1+R2)-d;    //interpenetración
  if(s>0){    //si hay colisión
    //calcular el vector normal 
    vector3D n = r21*(1.0/d);	      
    //calculo la fuerza
    vector3D F2=n*(Khertz*pow(s,1.5));
    //las sumo a los granos
    Planeta1.SumeFuerza(F2);  Planeta2.SumeFuerza(F2*(-1));
  }
  
}
//----------- Funciones Globales -----------
//---Funciones de Animacion---
void InicieAnimacion(void){
  //cout<<"set terminal gif animate"<<endl; 
  //cout<<"set output 'UnBalon.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange[-10:"<<Lx+10<<"]"<<endl;
  cout<<"set yrange[-10:"<<Ly+10<<"]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
    cout << "," <<Lx/7 << "*t,0";
    cout << "," <<Lx/7 << "*t,"<<Ly;
    cout << ",0," <<Lx/7 << "*t";
    cout << "," <<Lx <<","<< Ly/7<< "*t";
  
}
void TermineCuadro(void){
    cout<<endl;
    }

int main(){
  Cuerpo Planeta[N+4];
  Colisionador Newton;
  Crandom ran64(1);
  int ix, iy, i;
  //parámetros de la simulación
  double m0 = 1.0; double R0 = 2.0;
  double kT = 10;
  //variables auxiliares para la condición inicial
  double dx = Lx/(Nx+1);
  double dy = Ly/(Ny+1);
  double theta; double V0 = sqrt(kT/m0);
  double x0, y0, Vx0, Vy0;
  //variables auxiliares para las paredes
  double Rpared = 100*Lx, Mpared = 100*m0;
  //variables globales para correr la simulación
  int Ncuadros = 1000; double t, tdibujo, dt = 1e-3, ttotal = (Lx/V0), tcuadro = ttotal/Ncuadros;
  
 

    InicieAnimacion();
  
  //INICIO
  //Inicializar las paredes
    Planeta[N].Inicie(Lx/2, Ly + Rpared, 0, 0, 0, 0, Mpared, Rpared);    //pared arriba
    Planeta[N+1].Inicie(Lx/2, Ly - Rpared, 0, 0, 0, 0, Mpared, Rpared);  //pared abajo
    Planeta[N+2].Inicie(Lx + Rpared, Ly/2, 0, 0, 0, 0, Mpared, Rpared);  //pared derecha
    Planeta[N+3].Inicie(Lx - Rpared, Ly/2, 0, 0, 0, 0, Mpared, Rpared);  //pared izquierda

  //Inicializar los granos
    for(ix = 0; ix < Nx; ix++)
      for(iy = 0; iy < Ny; iy++){
	theta = 2*M_PI*ran64.r();
	x0=(ix+1)*dx; y0=(iy+1)*dy; Vx0=V0*cos(theta); Vy0=V0*sin(theta);
      }
  //---------------(x0,y0,z0,Vx0,   Vy0,Vz0,m0,R0)
  Planeta[iy*Nx+ix].Inicie(x0, y0, 0, Vx0, Vy0, 0, m0, R0);

  //CORRO
  for(t=tdibujo=0;t<ttotal;t+=dt,tdibujo+=dt){

    if(tdibujo>tcuadro){
      
            InicieCuadro();
	    for(i=0;i<N;i++);
	    Planeta[i].Dibujese();
      TermineCuadro();
      
      tdibujo=0;
    }
    //cout<<Planeta[1].Getx()<<" "<<Planeta[1].Gety()<<endl;

    
    for(i=0;i<N;i++) Planeta[i].Mueva_r(dt,xi);    
    Newton.CalculeTodasLasFuerzas(Planeta); for(i=0;i<N;i++) Planeta[i].Mueva_V(dt,Um2lambdau2);
    for(i=0;i<N;i++) Planeta[i].Mueva_r(dt,chi);
    Newton.CalculeTodasLasFuerzas(Planeta); for(i=0;i<N;i++) Planeta[i].Mueva_V(dt,lambda);
    for(i=0;i<N;i++) Planeta[i].Mueva_r(dt,Um2chiplusxi);
    Newton.CalculeTodasLasFuerzas(Planeta); for(i=0;i<N;i++)Planeta[i].Mueva_V(dt,lambda);
    for(i=0;i<N;i++) Planeta[i].Mueva_r(dt,chi);
    Newton.CalculeTodasLasFuerzas(Planeta); for(i=0;i<N;i++)Planeta[i].Mueva_V(dt,Um2lambdau2);
    for(i=0;i<N;i++) Planeta[i].Mueva_r(dt,xi);
    
  }
  return 0;
}
