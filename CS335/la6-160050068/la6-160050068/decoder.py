import sys
import numpy as np

np.random.seed(0)

def decode(gridfile,policyfile,p=1.0):
    f=open(policyfile,'r')
    lines=f.readlines()[0:-1]
    f.close()
    Pi=[int(lines[i][0:-1].split(" ")[1]) for i in range(len(lines))]
    f=open(gridfile,'r')
    lines=f.readlines()
    f.close()
    maze=[[int(x) for x in lines[i].split(" ")] for i in range(len(lines))]
    h=len(maze)
    w=len(maze[0])
    for i in range(h):
        for j in range(w):
            if maze[i][j]==3:
                endstate=i*h+j
            elif maze[i][j]==2:
                startstate=i*h+j
    cur=startstate
    moves=[[-1,0],[1,0],[0,-1],[0,1]]
    directions=['N ','S ','W ','E ']
    path=""   
    while cur!=endstate:
        count=0
        for k in range(4):
            i1=(cur//h)+moves[k][0]
            j1=(cur%w)+moves[k][1]
            if maze[i1][j1]!=1:
                count+=1
        probs=[0.0 for i in range(5)]
        for k in range(4):
            i1=(cur//h)+moves[k][0]
            j1=(cur%w)+moves[k][1]
            if k==Pi[cur]:
                t=p+(1-p)/count
            elif maze[i1][j1]==1:
                t=0
            else:
                t=(1-p)/count  
            probs[k+1]+=probs[k]+t
        r=np.random.random()
        # randomlist.append(r)
        ind=0
        for k in range(4):
            if r<probs[k+1] and r>=probs[k]:
                ind=k
        probs=[]
        path=path+directions[ind]
        cur=cur+moves[ind][0]*h+moves[ind][1]
    print(path)

if __name__=="__main__":
    if len(sys.argv) ==3:
        decode(sys.argv[1],sys.argv[2],1.0)
    elif len(sys.argv) ==4:
        decode(sys.argv[1],sys.argv[2],float(sys.argv[3]))
    # f=open(sys.argv[2],'w')




