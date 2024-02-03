class Node:
    def __init__(self, e):
        self.data = e
        self.next = None


class List:
    def __init__(self):
        self.head = None


'''
crearea unei liste din valori citite pana la 0
'''


def createList():
    lista = List()
    lista.head = createListRecursive()
    return lista


def createListRecursive():
    x = int(input("x= "))
    if x == 0:
        return None
    else:
        node = Node(x)
        node.next = createListRecursive()
        return node


'''
tiparirea elementelor unei liste
'''


def printList(lista):
    printListRecursive(lista.head)


def printListRecursive(node):
    if node is not None:
        print(node.data)
        printListRecursive(node.next)


def pushBackRecursive(node, data):
    if node is None:
        return Node(data)
    else:
        node.next = pushBackRecursive(node.next, data)
        return node


def concatenateTwoListsRecursive(firstListNode, secondListNode):
    if firstListNode is None:
        return secondListNode
    else:
        firstListNode.next = concatenateTwoListsRecursive(firstListNode.next, secondListNode)
        return firstListNode


'''
program pentru test
'''


def main():
    firstList = createList()
    print()
    printList(firstList)
    print()
    pushBackRecursive(firstList.head, 10)
    printList(firstList)

    secondList = createList()
    print()
    printList(secondList)
    print()

    concatenateTwoListsRecursive(firstList.head, secondList.head)
    printList(firstList)


main()
