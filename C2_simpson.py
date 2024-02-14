import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return np.cos(x)

def simpson(a,b,n):             #n es el número de intervalos (debe ser entero y par)
    n *= 2
    h = (b-a)/n                 #es el paso que damos 
    sum = 0

    for i in range(n+1):        #n+1 para que comience en 0 y termine en n (necesito el dato n-1)
        x = a + i*h
        if(i==0 or i==n):
            sum += f(x)
        elif(i%2 == 0):
            sum += 2*f(x)
        else:
            sum += 4*f(x)
    
    return sum*h/3

a = 0
b = np.pi/2
n = 50

print("La integral por Simpson da", simpson(a,b,n))

