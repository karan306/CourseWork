import numpy as np
import sys

def valueIteration(transitions,rewards,states,actions,gamma,endstates):

    V=[0.0 for i in range(states)]
    Pi=[-1 for i in range(states)]

    def expected_reward(s,a):
        ans=0
        for i in range(len(transitions[s][a])):
            if transitions[s][a][i][1]!=0:
                ans+=transitions[s][a][i][1]*(rewards[s][a][i]+gamma*V[transitions[s][a][i][0]])
        return ans

    converged=False
    time=0
    while not converged:
        time+=1
        converged=True
        for i in range(states):
            if i in endstates:
                continue
            m=0.0
            for j in range(actions):
                t=expected_reward(i,j)
                if t>m:
                    Pi[i]=j
                    m=t
            if abs(m-V[i])>1e-16:
                converged=False
            V[i]=m
    return V,Pi,time

def convert_data(filename):
    f=open(filename,'r')
    s=int(f.readline()[0:-1].split(" ")[-1])
    a=int(f.readline()[0:-1].split(" ")[-1])
    # print(s,a)
    f.readline()
    endstates=list(map(int,(f.readline()[0:-1].split(" "))[1:]))
    transitions=[[[] for i in range(a)] for j in range(s)]
    rewards=[[[] for i in range(a)] for j in range(s)]
    l=f.readline()[0:-1].split(" ")
    while l[0]!="discount":
        # print(l)
        transitions[int(l[1])][int(l[2])].append([int(l[3]),float(l[5])])
        rewards[int(l[1])][int(l[2])].append(float(l[4]))
        l=f.readline()[0:-1].split(" ")
    gamma=float(l[-1])
    # print(transitions,rewards)
    return s,a,transitions,rewards,gamma,endstates



if __name__=="__main__":
    s,a,transitions,rewards,gamma,endstates=convert_data(sys.argv[1])
    V,Pi,t=valueIteration(transitions,rewards,s,a,gamma,endstates)
    for i in range(s):
        print(V[i],Pi[i])
    print("iterations",t)

