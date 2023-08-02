import random
from copy import deepcopy


class UndirectedGraph:
    """An undirected graph, represented as two maps,
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

    def parseN(self, x):
        """Returns an iterable containing the outbound neighbours of x"""
        if self.isVertex(x):
            return self._dictOut[x]

    def parseEdges(self):
        """Returns an iterable containing all the edges with their costs"""
        edges = set()
        for x in self._dictOut:
            for y in self._dictOut[x]:
                if x < y:  # consider only edges with smaller vertex id first
                    edges.add((x, y, self._dictCost[(x, y)]))
        return sorted(edges, key=lambda v: (v[0], v[1]))

    def isVertex(self, vertex):
        """Returns True if the vertex exists, False otherwise"""
        return vertex in self._dictIn and vertex in self._dictOut

    def isEdge(self, x, y):
        """Returns True if there is an edge from x to y, False otherwise"""
        if x in self._dictOut:
            return y in self._dictOut[x]
        else:
            return False

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
        """Adds an undirected edge from vertex x to vertex y with the given cost"""
        if self.isEdge(x, y):
            raise ValueError("Edge already exits!")
        if self.isVertex(x) and self.isVertex(y):
            self._dictOut[x].append(y)
            self._dictIn[y].append(x)

            self._dictOut[y].append(x)
            self._dictIn[x].append(y)

            self._dictCost[(x, y)] = cost
            self._dictCost[(y, x)] = cost

    def removeEdge(self, x, y):
        """Removes the directed edge from vertex x to vertex y"""
        if not self.isEdge(x, y):
            raise ValueError("Edge does not exist!")
        self._dictOut[x].remove(y)
        self._dictIn[y].remove(x)

        self._dictOut[y].remove(x)
        self._dictIn[x].remove(y)

        del self._dictCost[(x, y)]
        del self._dictCost[(y, x)]

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
            self._dictCost[(y, x)] = cost
        else:
            raise ValueError("Edge does not exist!")

    def getNumEdges(self):
        return len(self._dictCost) // 2

    def generateRandom(self, n, m):
        """Generates a random graph with n vertices and m edges"""
        vertices = list(self.parseX())
        if m > n * (n - 1) // 2:
            raise ValueError("Too many edges for the given number of vertices!")
        edges = set()
        while len(edges) < m:
            x, y = random.sample(vertices, 2)
            if (x, y) not in edges and (y, x) not in edges:
                edges.add((x, y))
        for x, y in edges:
            cost = random.randint(1, 10)
            self.addEdge(x, y, cost)
        return self

    def copy(self):
        """
        Returns a deepcopy of the graph.
        """
        return deepcopy(self)

    def depthFirstTraversal(self, vertex, visited, component):
        stack = [vertex]
        while stack:
            current = stack.pop()
            visited.add(current)
            try:
                component.addVertex(current)
            except ValueError:
                continue
            for neighbour in self.parseN(current):
                if neighbour not in visited:
                    stack.append(neighbour)
                    try:
                        component.addEdge(current, neighbour, self.getEdgeInfo(current, neighbour))
                    except ValueError:
                        continue

    def connectedComponents(self):
        components = []
        visited = set()
        for vertex in self.parseX():
            if vertex not in visited:
                component = UndirectedGraph(0)
                self.depthFirstTraversal(vertex, visited, component)
                components.append(component)
        return components
