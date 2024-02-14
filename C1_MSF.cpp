#include <iostream>
#include <cmath>
using namespace std;

const double error = 1e-7;

double f(double x){
    return sin(x)/x;
}

int main(){

double a = 2, b = 4, m, fa, fm;
fa = f(a);

while(b-a>error){
    m = (b+a)/2;
    fm = f(m);

    if(fa*fm > 0){
    fa = fm;
    a = m;
    }

    else
    b = m;
}

    cout << "El cero es x = " << (b+a)/2 << endl;

    return 0;
}