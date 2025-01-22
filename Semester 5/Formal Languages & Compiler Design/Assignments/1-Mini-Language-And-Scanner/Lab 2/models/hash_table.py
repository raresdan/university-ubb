import copy


class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


class HashTable:
    def __init__(self):
        self.capacity = 2
        self.number_of_elements = 0
        self.elements_list = [None] * 2

    def hash(self, value):
        if isinstance(value, int):
            return value % self.capacity
        elif isinstance(value, str):
            return sum(ord(char) for char in value) % self.capacity

    def add(self, key, value):
        if self.number_of_elements and (self.capacity // self.number_of_elements < 2):
            self.resize_and_rehash()
        element = self.elements_list[self.hash(key)]
        if element is None:
            self.elements_list[self.hash(key)] = Node(key, value)
            self.number_of_elements += 1
            return
        while element.next is not None:
            element = element.next
        element.next = Node(key, value)
        self.number_of_elements += 1

    def get(self, key):
        element = self.elements_list[self.hash(key)]
        while element is not None:
            if element.key == key:
                return element.value
            element = element.next
        return None

    def pop(self, key):
        element = self.elements_list[self.hash(key)]
        if element is None:
            return None
        if element.key == key:
            self.elements_list[self.hash(key)] = element.next
            self.number_of_elements -= 1
            return element.value
        while element.next is not None:
            if element.next.key == key:
                value = element.next.value
                element.next = element.next.next
                self.number_of_elements -= 1
                return value
            element = element.next
        return None

    def resize_and_rehash(self):
        self.capacity *= 2
        copy_element_list = copy.deepcopy(self.elements_list)
        self.elements_list = [None] * self.capacity
        self.number_of_elements = 0
        for element in copy_element_list:
            copy_element = copy.deepcopy(element)
            while copy_element is not None:
                self.add(copy_element.key, copy_element.value)
                copy_element = copy_element.next