import copy
import random
import time


class Graph:
    def __init__(self, n):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges
        '''
        self.__out = {}

        for i in range(n):
            self.__out[i] = []

    def add_edge(self, x, y):
        '''Adds an edge from x to y. Return True on success, False if the edge already exists. Precond: x and y exists
        '''

        if y in self.__out[x]:
            return False

        self.__out[x].append(y)
        return True

    def parseX(self):
        '''Returns something that can be iterated and produces all the vertices of the graph
        '''
        return list(self.__out.keys())

    def parseNOut(self, x):
        return list(self.__out[x])

    def parseNIn(self, x):
        neigh = []

        for node in self.__out:
            if x in self.__out[node]:
                neigh.append(node)

        return neigh

    def isEdge(self, x, y):
        return y in self.__out[x]


class GraphWithInNbh:
    def __init__(self, n):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges
        '''
        self.__out = {}
        self.__in = {}

        for i in range(n):
            self.__out[i] = []
            self.__in[i] = []

    def add_edge(self, x, y):
        '''Adds an edge from x to y. Return True on success, False if the edge already exists. Precond: x and y exists
        '''

        if y in self.__out[x]:
            return False

        self.__out[x].append(y)
        self.__in[y].append(x)
        return True

    def parseX(self):
        '''Returns something that can be iterated and produces all the vertices of the graph
        '''
        return list(self.__out.keys())

    def parseNOut(self, x):
        return list(self.__out[x])

    def parseNIn(self, x):
        return list(self.__in[x])

    def isEdge(self, x, y):
        return y in self.__out[x]

    def removeEdge(self, x, y):
        if not y in self.__out[x]:
            return False

        self.__out[x].remove(y)
        self.__in[y].remove(x)

        return True


def print_graph(g):
    print("Outbound")
    for x in g.parseX():
        print(x, ":", end='')
        for y in g.parseNOut(x):
            print(y, ' ', end='')
        print()
    print("Inbound")
    for x in g.parseX():
        print(x, ":", end='')
        for y in g.parseNIn(x):
            print(y, ' ', end='')
        print()


def parse_graph(g):
    before = time.time()
    for x in g.parseX():
        for y in g.parseNOut(x):
            pass
    after = time.time()
    print("Parse NOut: %sms" % ((after - before) * 1000,))
    before = time.time()
    for x in g.parseX():
        for y in g.parseNIn(x):
            pass
    after = time.time()
    print("Parse NIn: %sms" % ((after - before) * 1000,))


def create_small_graph(ctor=Graph):
    g = ctor(3)
    for e in [(0, 0), (0, 1), (0, 2), (1, 2)]:
        g.add_edge(e[0], e[1])
    return g


def create_random_graph(n, m, ctor=Graph):
    '''Creates a graph with n vertices and m edges, constructed with constructor 'ctor'
    '''
    g = ctor(n)
    if m > n * n:
        raise Exception("too many edges")
    before = time.time()
    if m * 2 < n * n:
        number_of_added_edges = 0
        failed_attempts_at_adding_an_edge = 0
        while number_of_added_edges < m:
            x = random.randrange(n)
            y = random.randrange(n)
            if g.add_edge(x, y):
                number_of_added_edges += 1
            else:
                failed_attempts_at_adding_an_edge += 1
        print(f"There were {failed_attempts_at_adding_an_edge} failed attempts at adding an edge")
    else:
        for i in range(n):
            for j in range(n):
                g.add_edge(i, j)

        number_of_edges = n * n
        while number_of_edges > m:
            x = random.randrange(n)
            y = random.randrange(n)
            output = g.removeEdge(x, y)
            if output:
                number_of_edges -= 1

    after = time.time()
    print(f"Generating the graph took {after - before} seconds")
    return g


def main():
    n = 1000
    # g = create_small_graph(GraphWithInNbh)
    g = create_random_graph(n, n * n - 5, GraphWithInNbh)
    # print_graph(g)
    parse_graph(g)


main()
