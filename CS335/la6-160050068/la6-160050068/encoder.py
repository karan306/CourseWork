import sys

def encode(filename,p=1.0):
    f=open(filename,'r')
    lines=f.readlines()
    a=4
    maze=[[int(x) for x in lines[i].split(" ")] for i in range(len(lines))]
    moves=[[-1,0],[1,0],[0,-1],[0,1]]
    h=len(maze)
    w=len(maze[0])
    s=w*h
    transitions=[[[] for i in range(a)] for j in range(s)]
    rewards=[[[] for i in range(a)] for j in range(s)]
    for i in range(h):
        for j in range(w):
            if maze[i][j]==3:
                endstate=i*h+j
            elif maze[i][j]==2:
                startstate=i*h+j
    for i in range(h):
        for j in range(w):
            if maze[i][j]==1 or maze[i][j]==3:
                continue
            else:
                for k in range(a):
                    i1=i+moves[k][0]
                    j1=j+moves[k][1]
                    if maze[i1][j1]!=1:
                        count=0
                        for l in range(a):
                            i2=i+moves[l][0]
                            j2=j+moves[l][1]
                            if maze[i2][j2]!=1:
                                count+=1
                        # print(moves[k],i,j)
                        # print(i1*h+j1)
                        transitions[i*h+j][k].append([i1*h+j1,p+(1.0-p)/count])
                        if maze[i1][j1]==3:
                            rewards[i*h+j][k].append(100.0)
                        else:
                            rewards[i*h+j][k].append(0.0)
                        if p==1.0:
                            continue
                        
                        for l in range(a):
                            if l!=k:
                                i2=i+moves[l][0]
                                j2=j+moves[l][1]
                                if maze[i2][j2]!=1:
                                    transitions[i*h+j][k].append([i2*h+j2,(1.0-p)/count])
                                    if maze[i2][j2]==3:
                                        rewards[i*h+j][k].append(100.0)
                                    else:
                                        rewards[i*h+j][k].append(0.0)
                                # else:
                                #     rewards[i*h+j][k].append(0)
                                #     transitions[i*h+j][k].append([i*h+j,(1.0-p)/3])
    return transitions,rewards,s,a,startstate,endstate

# def decode(filename):

if __name__=="__main__":
    if len(sys.argv)==2:
        transitions,rewards,s,a,startstate,endstate=encode(sys.argv[1],1.0)
    elif len(sys.argv)==3:
        transitions,rewards,s,a,startstate,endstate=encode(sys.argv[1],float(sys.argv[2]))
    # f=open(sys.argv[2],'w')
    print("numStates",s)
    print("numActions",a)
    print("start",startstate)
    print("end",endstate)
    for i in range(s):
        for j in range(a):
            for k in range(len(transitions[i][j])):
                print("transition",i,j,transitions[i][j][k][0],rewards[i][j][k],transitions[i][j][k][1])
    print("discount",0.9)

