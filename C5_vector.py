import numpy as np
import matplotlib.pyplot as plt

g = 9.8
dt = 0.01
nsteps = 100

class object:
    def __init__(self,x0,y0,z0,Vx0,Vy0,Vz0,m0):
        self.m=m0
        self.r=np.array([x0,y0,z0])
        self.V=np.array([Vx0,Vy0,Vz0])
    def calcf(self):
        self.F=np.array([0,-m*g,0])
    def move(self,dt):
        self.r+=dt*self.V
        self.V+=(dt/self.m)*self.F


xdata=np.zeros(nsteps)
ydata=np.zeros(nsteps)
ball = object(x0=0,y0=0,z0=0,Vx0=16,Vy0=9,Vz0=0,m0=0.453)
for i in range(nsteps):
    t=i*dt
    xdata[i]=ball.r[0]
    ydata[i]=ball.r[1]
    ball.calcf()
    ball.move(dt)



