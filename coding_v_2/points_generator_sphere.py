# import uniform distribution
from scipy.stats import uniform
import math
# random numbers from uniform distribution

r = 1
unit_delta = 0.0001


tipe = "uniform"
n = 100
start = 0
width = 1
x = uniform.rvs(size=n, loc = start, scale=width)
delta = uniform.rvs(size=n, loc = -unit_delta, scale=2*unit_delta)

y = list()
for z in x:
  y.append(math.sqrt(pow(r,2) - pow(z,2)))


x_delta = list()
y_delta = list()
for i in range(len(x)):
    x_delta.append(x[i]+delta[i])
    y_delta.append(y[i]+delta[i])


namefile= "data.txt"
f = open(namefile, "a")

for i in range(len(x_delta)):
  if(i != len(x_delta)-1):
    f.write("{"+str(x_delta[i])+", "+str(y_delta[i])+"}"+"\n")
  else:
    f.write("{"+str(x_delta[i])+", "+str(y_delta[i])+"}")
f.close()