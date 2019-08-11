import util
from sudoku import SudokuSearchProblem
from maps import MapSearchProblem
import networkx as nx
import osmnx as ox
import itertools

################ Node structure to use for the search algorithm ################
class Node:
    def __init__(self, state, action, path_cost, parent_node, depth):
        self.state = state
        self.action = action
        self.path_cost = path_cost
        self.parent_node = parent_node
        self.depth = depth

########################## DFS for Sudoku ########################
## Choose some node to expand from the frontier with Stack like implementation
def sudokuDepthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.
    """

    def convertStateToHash(values):
        """ 
        values as a dictionary is not hashable and hence cannot be used directly in the explored set.
        This function changes values dict into a unique hashable string which can be used in the explored set.
        """
        l = list(sorted(values.items()))
        modl = [a+b for (a, b) in l]
        return ''.join(modl)

    visited=util.Counter()
    searchstack=util.Stack()
    searchstack.push(problem.getStartState())
    visited[convertStateToHash(problem.getStartState())]=1
    while not searchstack.isEmpty():
        curstate=searchstack.pop()
        if (problem.isGoalState(curstate)):
            return curstate
        for s in problem.getSuccessors(curstate):
            v=s[0]
            if visited[convertStateToHash(v)]==0:
                visited[convertStateToHash(curstate)]=1
                searchstack.push(s[0])
    return False

    

    ## YOUR CODE HERE
    # util.raiseNotDefined()

######################## A-Star and DFS for Map Problem ########################
## Choose some node to expand from the frontier with priority_queue like implementation

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def heuristic(state, problem):
    point1=((problem.G.node[problem.end_node]['x'],0,0),(problem.G.node[problem.end_node]['y'],0,0))
    point2=((problem.G.node[state]['x'],0,0),(problem.G.node[state]['y'],0,0))
    return util.points2distance(point1,point2)
    # It would take a while for Flat Earther's to get accustomed to this paradigm
    # but hang in there.


def AStar_search(problem, heuristic=nullHeuristic):

    """Search the node that has the lowest combined cost and heuristic first."""
    parent=util.Counter()
    visited=util.Counter()
    p=util.PriorityQueue()
    nodes=problem.G.nodes
    u=problem.start_node
    v=problem.end_node
    s=util.Stack()
    s.push(v)
    f=util.Counter()   #minimum seen value of g+h
    g=util.Counter()   #cost function g
    h=util.Counter()   #heuristic function h
    g[u]=0
    for node in nodes:
        f[node]=999999999999
    for _ in range(len(nodes)):
        visited[u]=1
        if u==v:
            break
        for child in problem.getSuccessors(u):
            if visited[child[0]]==0:
                # print j
                if h[child[0]]==0:
                    h[child[0]]=heuristic(child[0],problem)
                val=g[u]+child[2]+h[child[0]]
                if f[child[0]]>val:
                    g[child[0]]=g[u]+child[2]
                    parent[child[0]]=u
                    f[child[0]]=val
                    p.push(child[0],val)
        temp=p.pop()
        # g[temp]=g[u]+problem.G.get_edge_data(u,temp)[0]['length']
        while visited[temp]==1:
            temp=p.pop()
        u=temp
    n=v
    # print(g)
    while n!=problem.start_node:
        s.push(parent[n])
        n=parent[n]
    l=[]
    while not s.isEmpty():
        l.append(s.pop())
    return l

    


        