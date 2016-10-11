import random
import math
import time

def decreaseTemperature(initialTemperature, i):
    return initialTemperature / i

def getTransitionProbability(dE, T):
    return math.exp(-dE / T)

def isTransition(probability):
    trigger = random.uniform(0, 1)
    
    if trigger < probability:
        return True
    else:
        return False

def calculateEnergy(path):
    pathPairs = zip(path[0::1],path[1::1])
    energy = len(pathPairs)
    return energy

def generateStateCandidate(path, availableEdges, G):
    if len(path) == 1: # Path is equal to node
        path = list(random.choice(availableEdges)) # Take any edge as a new path
        availableEdges = []
        for edge in G.edges():
            availableEdges.append(edge)
            availableEdges.append(edge[::-1])
        availableEdges.remove(tuple(path))
        availableEdges.remove(tuple(path[::-1]))

    if random.choice([True, True, False]): # Add new edge
    
        if not availableEdges: # All edges are in path
#             print "No available edges"
            return path, availableEdges
            
        # Path consists from one edge or more
        if random.choice([True, False]): # Add edge to the start
#             print "Add to start"
            nodeCandidates = G.nodes()
            random.shuffle(nodeCandidates)
            for node in nodeCandidates:
                if (node, path[0]) in availableEdges and (path[0], node) in availableEdges and node != path[-1] and node not in path:
#                     print "Adding node - ", node
                    path.insert(0, node)
#                     print "New path - ", path
                    availableEdges.remove((path[0], path[1]))
                    availableEdges.remove((path[1], path[0]))
                    break
        else: # Add edge to the end
#             print "Add to end"
            nodeCandidates = G.nodes()
            random.shuffle(nodeCandidates)
            for node in nodeCandidates:
                if (node, path[-1]) in availableEdges and (path[-1], node) in availableEdges and node != path[0] and node not in path:
#                     print "Adding node - ", node
                    path.append(node)
#                     print "New path - ", path
                    availableEdges.remove((path[-1], path[-2]))
                    availableEdges.remove((path[-2], path[-1]))
                    break
        
    else: # Remove edge
        if random.choice([True, False]): # Remove start edge
#             print "Remove start node - ", path[0]
            availableEdges.append((path[0], path[1]))
            availableEdges.append((path[1], path[0]))
            path.pop(0)
        else: # Remove end edge
#             print "Remove end node - ", path[-1]
            availableEdges.append((path[-1], path[-2]))
            availableEdges.append((path[-2], path[-1]))
            path.pop(-1)
    
    return path, availableEdges