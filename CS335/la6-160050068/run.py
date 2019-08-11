import os
import matplotlib.pyplot as plt

lis = []
prob = []
for i in range(11):
	prob.append(i*0.1)
for p in prob:
	os.system("./test.sh data/maze/grid10.txt data/maze/solution10.txt " + str(p))
	f = open("foo.txt", "r")
	lis.append(len(f.read().split()))

print(lis)
plt.plot(prob,lis)
plt.xlabel("Probabily value")
plt.ylabel("Number of actions required")

plt.show()