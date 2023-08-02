class WolfGoatCabbageVertex:
    def __init__(self, state):
        # 0 - W
        # 1 - G
        # 2 - C
        # 3 - B
        self.__representation = state 
     
    def __hash__(self):
        return self.__representation
    def __eq__(self, other):
        if not isinstance(other, WolfGoatCabbageVertex):
            return False
        return self.__representation == other.__representation
    def parseN(self):
        candidate = self.__representation
        for i in range(4):
            candidate = self.__representation^((1<<i) | 8)
            yield WolfGoatCabbageVertex(candidate)
            
    def is_valid(self):
        pass #TODO

    def __repr__(self):
        left_side = []
        right_side = []
        names = ['W', 'G', 'C', 'B']
        for i in range(4):
            if (self.__representation & (1<<i)) != 0:
                right_side.append(names[i])
            else:
                left_side.append(names[i])
        return " ".join(left_side) + "|" + " ".join(right_side)

    def __str__(self):
        return self.__repr__()

class WolfGoatCabbageGraph:
    def parseX(self):
        '''Returns something that can be iterated and produces all the vertices of the graph
        '''
        raise Exception("Not implemented")
    
    def parseNOut(self, x):
        return x.parseN()
        
    def parseNIn(self, x):
        return x.parseN()
        
    def isEdge(self, x, y):
        for v in x.parseN():
            if v == y:
                return True
        return False
    
    def start(self):
        return WolfGoatCabbageVertex(0)

    def dest(self):
        return WolfGoatCabbageVertex(15)
