from source.graph.graph import DirectedGraph


class Ui:
    def __init__(self):
        self.graph = DirectedGraph(0)
        self.copy = DirectedGraph(0)

    def emptyGraph(self):
        self.graph = DirectedGraph(0)
        print("Graph created successfully!")

    def randomGraph(self):
        try:
            n = int(input("Enter the number of vertices: "))
        except ValueError as ve:
            print("Number of vertices must be an integer!", ve)
            return
        try:
            m = int(input("Enter the number of edges: "))
        except ValueError as ve:
            print("Number of edges must be an integer!", ve)
            return
        self.graph = DirectedGraph(n)
        try:
            self.graph.generateRandom(n, m)
        except ValueError as ve:
            print(ve)
        return self.graph

    def addNextVertex(self):
        """Adds a vertex to the graph"""
        try:
            self.graph.addVertex(len(self.graph.parseX()))
        except ValueError as ve:
            print(ve)
        print("Vertex added.")

    def addVertexUi(self):
        """Adds a vertex to the graph"""
        try:
            v = int(input("Enter the new vertex: "))
        except ValueError as ve:
            print("Vertex must be an integer!", ve)
            return
        try:
            self.graph.addVertex(v)
            print("Vertex added.")
        except ValueError as ve:
            print(ve)

    def addEdgeUi(self):
        """Adds an edge to the graph"""
        try:
            x = int(input("Enter the source vertex: "))
        except ValueError as ve:
            print("Source vertex must be an integer!", ve)
            return
        try:
            y = int(input("Enter the target vertex: "))
        except ValueError as ve:
            print("Target vertex must be an integer!", ve)
            return
        try:
            c = int(input("Enter the cost of the edge: "))
        except ValueError as ve:
            print("Cost must be an integer!", ve)
            return
        if not self.graph.isEdge(x, y):
            try:
                self.graph.addEdge(x, y, c)
            except ValueError as ve:
                print(ve)
                return
            print("Edge added.")
        else:
            print("Edge already exists.")

    def removeVertexUi(self):
        """Removes a vertex from the graph"""
        try:
            v = int(input("Enter the vertex to remove: "))
        except ValueError as ve:
            print("Vertex must be an integer!", ve)
            return
        try:
            self.graph.removeVertex(v)
        except ValueError as ve:
            print(ve)
            return
        print("Vertex removed.")

    def removeEdgeUi(self):
        """Removes an edge from the graph"""
        try:
            x = int(input("Enter the source vertex: "))
        except ValueError as ve:
            print("Source vertex must be an integer!", ve)
            return
        try:
            y = int(input("Enter the target vertex: "))
        except ValueError as ve:
            print("Target vertex must be an integer!", ve)
            return
        if self.graph.isEdge(x, y):
            try:
                self.graph.removeEdge(x, y)
            except ValueError as ve:
                print(ve)
            print("Edge removed.")
        else:
            print("Edge does not exist.")

    def updateEdgeCost(self):
        try:
            x = int(input("Enter the source vertex: "))
        except ValueError as ve:
            print("Source vertex must be an integer!", ve)
            return
        try:
            y = int(input("Enter the target vertex: "))
        except ValueError as ve:
            print("Target vertex must be an integer!", ve)
            return
        try:
            c = int(input("Enter the new cost of the edge: "))
        except ValueError as ve:
            print("Cost must be an integer!", ve)
            return
        if self.graph.isEdge(x, y):
            try:
                self.graph.setEdgeInfo(x, y, c)
            except ValueError as ve:
                print(ve)
        else:
            print("Edge does not exist.")

    def printCost(self):
        try:
            x = int(input("Enter the source vertex: "))
        except ValueError as ve:
            print("Source vertex must be an integer!", ve)
            return
        try:
            y = int(input("Enter the target vertex: "))
        except ValueError as ve:
            print("Target vertex must be an integer!", ve)
            return
        if self.graph.getEdgeInfo(x, y) is not None:
            c = self.graph.getEdgeInfo(x, y)
            print(f"The cost of the edge ({x},{y}) is {c}!")
        else:
            print("Edge does not exist.")

    def printInDegree(self):
        try:
            v = int(input("Enter the vertex: "))
        except ValueError as ve:
            print("Vertex must be an integer!", ve)
            return
        print(self.graph.getInDegree(v))

    def printOutDegree(self):
        try:
            v = int(input("Enter the vertex: "))
        except ValueError as ve:
            print("Vertex must be an integer!", ve)
            return
        print(self.graph.getOutDegree(v))

    def printNumVertices(self):
        print(self.graph.getNumVertices())

    def printNumEdges(self):
        print(self.graph.getNumEdges())

    def checkVertex(self):
        try:
            v = int(input("Enter the vertex: "))
        except ValueError as ve:
            print("Vertex must be an integer!", ve)
            return
        if self.graph.isVertex(v):
            print(f"{v} is a vertex in the graph!")
        else:
            print(f"{v} is not a vertex in the graph!")

    def checkEdge(self):
        try:
            x = int(input("Enter the source vertex: "))
        except ValueError as ve:
            print("Source vertex must be an integer!", ve)
            return
        try:
            y = int(input("Enter the target vertex: "))
        except ValueError as ve:
            print("Target vertex must be an integer!", ve)
            return
        if self.graph.isEdge(x, y):
            print(f"({x},{y}) is an edge in the graph!")
        else:
            print(f"({x},{y}) is not an edge in the graph!")

    def printVertices(self):
        print(list(self.graph.parseX()))

    def printNin(self):
        try:
            v = int(input("Enter the vertex: "))
        except ValueError as ve:
            print("Vertex must be an integer!", ve)
            return
        print(self.graph.parseNin(v))

    def printNout(self):
        try:
            v = int(input("Enter the vertex: "))
        except ValueError as ve:
            print("Vertex must be an integer!", ve)
            return
        print(self.graph.parseNout(v))

    def printEdges(self):
        for edge in self.graph.parseEdges():
            print(edge)

    def printGraph(self):
        """Prints the graph"""
        for v in self.graph.parseX():
            print("Vertex", v, ":")
            print("  Outbound neighbors:", list(self.graph.parseNout(v)))
            print("  Inbound neighbors:", list(self.graph.parseNin(v)))

    def copyGraph(self):
        """Copies the graph"""
        self.copy = self.graph.copy()
        print("Graph copied.")

    def readGraph(self):
        """Reads a graph from a file"""
        try:
            filename = input("Enter the filename: ")
            with open(filename, 'r') as file:
                n, m = map(int, file.readline().split())
                self.graph = DirectedGraph(n)
                for i in range(m):
                    x, y, c = map(int, file.readline().split())
                    try:
                        self.graph.addEdge(x, y, c)
                    except ValueError as ve:
                        print(ve)
                        return
        except FileNotFoundError:
            print("File not found.")
            return
        print("Graph read from file.")
        return self.graph

    def readGraph2(self):
        """Reads a graph from a file"""
        try:
            filename = input("Enter the filename: ")
            with open(filename, 'r') as file:
                n, m = map(int, file.readline().split())
                self.graph = DirectedGraph(n)
                for i in range(m):
                    x, y, c = map(int, file.readline().split())
                    try:
                        self.graph.addEdge(x, y, c)
                    except ValueError as ve:
                        print(ve)
                        return
                for v in range(n - self.graph.getNumVertices()):
                    self.graph.addVertex(v)
        except FileNotFoundError:
            print("File not found.")
            return
        print("Graph read from file.")
        return self.graph

    def writeGraph(self):
        """Writes the graph to a file"""
        vertices = []
        filename = input("Enter the filename: ")
        with open(filename, 'w') as file:
            file.write(str(self.graph.getNumVertices()) + " " + str(self.graph.getNumEdges()) + "\n")
            for v in self.graph.parseX():
                vertices.append(v)
            for v in self.graph.parseX():
                for u in self.graph.parseNout(v):
                    file.write(str(v) + " " + str(u) + " " + str(self.graph.getEdgeInfo(v, u)) + "\n")
                    if v in vertices:
                        vertices.remove(v)
                    if u in vertices:
                        vertices.remove(u)
            for v in vertices:
                file.write(str(v) + "\n")
        print("Graph written to file.")

    def revertCopy(self):
        self.graph = self.copy

    def floydWarshallUi(self):
        try:
            x = int(input("Enter the source vertex: "))
        except ValueError as ve:
            print("Source vertex must be an integer!", ve)
            return
        try:
            y = int(input("Enter the target vertex: "))
        except ValueError as ve:
            print("Target vertex must be an integer!", ve)
            return
        print()
        path, distance = self.graph.floydWarshall(x, y)
        print(f"Path: {path}, Distance: {distance}")

    @staticmethod
    def menu():
        print("------------Menu------------")
        print()
        print("GENERATE A GRAPH")
        print("1. Generate empty graph")
        print("2. Generate a random graph with n vertices and m edges")
        print()
        print("GRAPH OPERATIONS")
        print("3. Add next vertex")
        print("4. Add specific vertex")
        print("5. Remove vertex")
        print("6. Add edge")
        print("7. Remove edge")
        print("8. Modify the cost of an edge")
        print()
        print("GRAPH PROPERTIES")
        print("9. Print the cost of an edge")
        print("10. Print the in degree of a vertex")
        print("11. Print the out degree of a vertex")
        print("12. Print the number of vertices")
        print("13. Print the number of edges")
        print("14. Check if a vertex belongs to the graph")
        print("15. Check if an edge belongs to the graph")
        print("16. Print the list of vertices")
        print("17. Print the list of outbound neighbours of a vertex")
        print("18. Print the list of inbound neighbours of a vertex")
        print("19. Print the list of edges")
        print()
        print("READ/WRITE/COPY/PRINT GRAPH")
        print("20. Print the graph")
        print("21. Copy the graph")
        print("22. Read the graph from predefined file")
        print("23. Read the graph from written file")
        print("24. Write the graph to file")
        print("25. Revert to last copy made")
        print()
        print("FLOYD MARSHALL ALGORITHM")
        print("26. Lowest cost walk")
        print()
        print("0. Exit")

    def run_menu(self):
        while True:
            self.menu()
            while True:
                try:
                    print()
                    option = int(input("Enter your option: "))
                    print()
                    break
                except ValueError as ve:
                    print("Invalid option!", ve)

            if option == 1:
                self.emptyGraph()
            elif option == 2:
                self.randomGraph()
            elif option == 3:
                self.addNextVertex()
            elif option == 4:
                self.addVertexUi()
            elif option == 5:
                self.removeVertexUi()
            elif option == 6:
                self.addEdgeUi()
            elif option == 7:
                self.removeEdgeUi()
            elif option == 8:
                self.updateEdgeCost()
            elif option == 9:
                self.printCost()
            elif option == 10:
                self.printInDegree()
            elif option == 11:
                self.printOutDegree()
            elif option == 12:
                self.printNumVertices()
            elif option == 13:
                self.printNumEdges()
            elif option == 14:
                self.checkVertex()
            elif option == 15:
                self.checkEdge()
            elif option == 16:
                self.printVertices()
            elif option == 17:
                self.printNout()
            elif option == 18:
                self.printNin()
            elif option == 19:
                self.printEdges()
            elif option == 20:
                self.printGraph()
            elif option == 21:
                self.copyGraph()
            elif option == 22:
                self.readGraph()
            elif option == 23:
                self.readGraph2()
            elif option == 24:
                self.writeGraph()
            elif option == 25:
                self.revertCopy()
            elif option == 26:
                self.floydWarshallUi()
            elif option == 0:
                print("Menu exited successfully!")
                break
            else:
                print("Invalid option!")
