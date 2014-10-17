import numpy as np
from scipy.misc import factorial
import matplotlib.pyplot as plt

def digit_factorial(x):
    a = x.copy()
    s = np.zeros(x.size,dtype=np.int32)
    while a.any():
        s += factorial(a % 10) - (a == 0)
        a //= 10
    return s


n = 50000
x = np.arange(n,dtype=np.int32)
y = digit_factorial(x)
plt.plot(x,y-x,'o')
plt.plot(x,np.zeros(x.size))

x1,x2,y1,y2 = plt.axis()
plt.axis((x1,x2,-10,10))

plt.show()

k = np.where(y == x)
k
