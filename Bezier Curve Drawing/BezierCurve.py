import numpy as np
import matplotlib.pyplot as plt


def nchoosek(n,p):
    if p == 0:
        return 1
    if n ==0:
        return 0
    elif p>n:
        return 0
    elif p == n :
        return 1
    else:
        return nchoosek(n-1,p)+nchoosek(n-1,p-1)

def Bernstein(N,t):
    BNt = []
    for i in range(N+1):
        Pol = nchoosek(N,i)*t**i*(1-t)**(N-i)
        BNt.append(Pol)
    BNt = np.array(BNt)
    return BNt


def PlotBezierCurve(Polygon):
    t = np.linspace(0,1,100)
    Bezier = []
    for x in t:
        Bezier.append(np.dot(Polygon,Bernstein(len(Polygon[1])-1,x)))
        #Bezier.append(np.dot(Polygon,np.transpose(Bernstein(len(Polygon[1])-1,x))))
        absc = [Bezier[i][0] for i in range(len(Bezier))]
        ordo = [Bezier[i][1] for i in range(len(Bezier))]
    plt.draw()
    plt.plot(absc,ordo,label='Bezier curve')
    plt.legend()
    plt.show()
    return


def AcquisitionPolygone(minmax,color1,color2) :
    x = []
    y = []
    coord = 0
    while coord != []:
        coord = plt.ginput(1, mouse_add=1, mouse_stop=3, mouse_pop=2)
        if coord != []:
            plt.draw()
            xx = coord[0][0]
            yy = coord[0][1]
            plt.plot(xx,yy,color1,ms=8)
            x.append(xx)
            y.append(yy)
            if len(x) > 1 :
                plt.plot([x[-2],x[-1]],[y[-2],y[-1]],color2)
    
    Polygon = np.zeros((2,len(x)))
    Polygon[0,:] = x
    Polygon[1,:] = y
    return Polygon




fig2 = plt.figure()
ax = fig2.add_subplot(111)
minmax = 10
ax.set_xlim((-minmax,minmax))
ax.set_ylim((-minmax,minmax))
plt.title("Polygon acquisition and Bezier curve")
Poly = AcquisitionPolygone(minmax,'or',':r')
PlotBezierCurve(Poly)# This function has to be defined
plt.waitforbuttonpress()
