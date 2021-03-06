import matplotlib.pyplot as plt
import numpy as np
import csv

t = []
phi = []
r = []
chi = []

#with open('e_023_r1_526.txt', 'r') as csvfile:
with open('data4.txt', 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter = ',')
    for row in plots:
        t.append(float(row[0]))
        phi.append(float(row[1]))
        r.append(float(row[2]))
        chi.append(float(row[3]))
      
#plt.plot(t, r, label='r(t)')
#plt.plot(t[1], r[1], 'ro')
#plt.plot(chi, r, label = 'r(chi)')
#plt.plot(chi, t, label='phi(chi)')
#plt.plot(chi, r*np.cos(phi), label='rcos(phi), chi')
#plt.plot(chi, r*np.sin(phi), label='rsin(phi), chi')
plt.plot(r*np.cos(phi), r*np.sin(phi), label='rsin(phi), rcos(phi)')
plt.plot(r[1]*np.cos(phi[1]), r[1]*np.sin(phi[1]),'ro', label='rsin(phi), rcos(phi)')
plt.legend()
plt.show()

