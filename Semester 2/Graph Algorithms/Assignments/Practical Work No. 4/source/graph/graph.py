import random
from copy import deepcopy


class DirectedGraph:
    """A directed graph, represented as two maps,
    one from each vertex to the set of outbound neighbours,
    the other from each vertex to the set of inbound neighbours"""

    def __init__(self, n):
        """Creates a graph with n vertices (numbered from 0 to n-1)
        and no edges"""
        self._dictOut = {}
        self._dictIn = {}
        self._dictCost = {}
        for i in range(n):
            self._dictOut[i] = []
            self._dictIn[i] = []

    def parseX(self):
        """Returns an iterable containing all the vertices"""
        return self._dictOut.keys()

    def parseNout(self, x):
        """Returns an iterable containing the outbound neighbours of x"""
        if self.isVertex(x):
            return self._dictOut[x]

    def parseNin(self, x):
        """Returns an iterable containing the inbound neighbours of x"""
        if self.isVertex(x):
            return self._dictIn[x]

    def parseEdges(self):
        """Returns an iterable containing all the edges with their costs"""
        edges = []
        for x in self._dictOut:
            for y in self._dictOut[x]:
                edges.append((x, y, self._dictCost[(x, y)]))
        return edges

    def isVertex(self, vertex):
        """Returns True if the vertex exists, False otherwise"""
        return vertex in self._dictIn and vertex in self._dictOut

    def isEdge(self, x, y):
        """Returns True if there is an edge from x to y, False otherwise"""
        if x in self._dictOut:
            return y in self._dictOut[x]
        else:
            return False

    def getInDegree(self, vertex):
        """Returns the in-degree of vertex x"""
        if self.isVertex(vertex):
            return len(self._dictIn[vertex])
        return 0

    def getOutDegree(self, vertex):
        """Returns the out-degree of vertex x"""
        if self.isVertex(vertex):
            return len(self._dictOut[vertex])
        return 0

    def addVertex(self, vertex):
        if self.isVertex(vertex):
            raise ValueError("Vertex already exists!")
        self._dictIn[vertex] = []
        self._dictOut[vertex] = []

    def removeVertex(self, vertex):
        """Removes the vertex and all the edges that contain it.
        If the vertex does not exist, raises an Exception."""
        if not self.isVertex(vertex):
            raise ValueError("Vertex does not exist!")
        for u in self._dictIn[vertex]:
            self.removeEdge(u, vertex)
        for u in self._dictOut[vertex]:
            self.removeEdge(vertex, u)
        del self._dictIn[vertex]
        del self._dictOut[vertex]

    def getNumVertices(self):
        """Returns the number of vertices in the graph"""
        return len(self._dictOut)

    def addEdge(self, x, y, cost=0):
        """Adds a directed edge from vertex x to vertex y with the given cost"""
        if self.isEdge(x, y):
            raise ValueError("Edge already exits!")
        # if self.isEdge(y, x) and cost != self.getEdgeInfo(y, x):
        #     raise ValueError(f"Cost of ({x},{y}) must be the same as cost of ({y},{x})!")
        if self.isVertex(x) and self.isVertex(y):
            self._dictOut[x].append(y)
            self._dictIn[y].append(x)
            self._dictCost[(x, y)] = cost

    def removeEdge(self, x, y):
        """Removes the directed edge from vertex x to vertex y"""
        if not self.isEdge(x, y):
            raise ValueError("Edge does not exist!")
        self._dictOut[x].remove(y)
        self._dictIn[y].remove(x)
        del self._dictCost[(x, y)]

    def getEdgeInfo(self, x, y):
        """Returns the information (integer) attached to the specified edge (x, y),
        or None if the edge does not exist"""
        if self.isEdge(x, y):
            return self._dictCost[(x, y)]
        else:
            return None

    def setEdgeInfo(self, x, y, cost):
        """Sets the information (integer) attached to the specified edge (x, y)
        to the given value. If the edge does not exist, raises an Exception."""
        if self.isEdge(x, y):
            self._dictCost[(x, y)] = cost
        else:
            raise ValueError("Edge does not exist!")

    def getNumEdges(self):
        return len(self._dictCost)

    def generateRandom(self, n, m):
        """Generates a random graph with n vertices and m edges"""
        if m > n * (n - 1):
            raise ValueError("Too many edges!")
        self._dictOut = {}
        self._dictIn = {}
        self._dictCost = {}
        for i in range(n):
            self._dictOut[i] = []
            self._dictIn[i] = []
        edges = set()
        while len(edges) < m:
            x = random.randint(0, n - 1)
            y = random.randint(0, n - 1)
            if x == y or (x, y) in edges:
                continue
            self.addEdge(x, y, random.randint(0, 1000))
            edges.add((x, y))
        return self

    def copy(self):
        """
        Returns a deepcopy of the graph.
        """
        return deepcopy(self)

    def findHighestCostPath(self, start, end):
        if not self.isVertex(start) or not self.isVertex(end):
            raise ValueError("Invalid vertices!")
        # Initialize the maximum costs and predecessor arrays
        maxCosts = [-float('inf')] * self.getNumVertices()
        maxCosts[start] = 0
        predecessors = [None] * self.getNumVertices()
        # Perform topological sorting based on predecessor counters
        inDegrees = [self.getInDegree(vertex) for vertex in self.parseX()]
        queue = []
        for vertex in self.parseX():
            if inDegrees[vertex] == 0:
                queue.append(vertex)
        topologicalOrder = []
        count = 0
        while queue:
            vertex = queue.pop(0)
            topologicalOrder.append(vertex)
            count += 1
            for neighbor in self.parseNout(vertex):
                cost = self.getEdgeInfo(vertex, neighbor)
                newCost = maxCosts[vertex] + cost
                # Update the maximum cost and predecessor for the neighbor
                if newCost > maxCosts[neighbor]:
                    maxCosts[neighbor] = newCost
                    predecessors[neighbor] = vertex
                inDegrees[neighbor] -= 1
                if inDegrees[neighbor] == 0:
                    queue.append(neighbor)
        print("Topological Sorting Order:", topologicalOrder)
        if count != self.getNumVertices():
            raise ValueError("The graph is not a DAG!")
        if maxCosts[end] == float('-inf'):
            return None, None
        # Reconstruct the highest cost path from start to end
        path = []
        current = end
        while current is not None:
            path.append(current)
            current = predecessors[current]
        path.reverse()
        return maxCosts[end], path
