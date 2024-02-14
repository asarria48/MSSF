import numpy as np
import matplotlib.pyplot as plt

def f(t,x,n):
    return np.cos(n*t - x*np.sin(t))

def simpson(a,b,nsteps,x,n):             #n es el número de intervalos (debe ser entero y par)
    nsteps *= 2
    h = (b-a)/nsteps                 #es el paso que damos 
    sum = 0

    for i in range(nsteps+1):        #n+1 para que comience en 0 y termine en n (necesito el dato n-1)
        t = a + i*h
        if(i==0 or i==nsteps):
            sum += f(t,x,n)
        elif(i%2 == 0):
            sum += 2*f(t,x,n)
        else:
            sum += 4*f(t,x,n)
    
    return sum*h/3

def bessel(n,x):
    return (1/np.pi)*simpson(0,np.pi,100,x,n)


#GRAFICAR

n = 0
a = 0
b = 10
Nsteps = 100
dx = (b-a)/Nsteps
xdata = np.zeros(Nsteps)
ydata = np.zeros(Nsteps)

for i in range(Nsteps):
    x = a + i*dx
    xdata[i] = x
    ydata[i] = bessel(n,x)

plt.plot(xdata, ydata)
plt.show()

