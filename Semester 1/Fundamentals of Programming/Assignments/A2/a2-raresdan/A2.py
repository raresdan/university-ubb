# I was assigned: Bubble Sort & Comb Sort
import random


def bubble_sort(v):
    l = len(v)
    # l is the length of the array
    steps = int(input("Enter steps: "))
    for i in range(0, l):
        for j in range(0, l - i - 1):
            if v[j] > v[j + 1]:
                aux = v[j]
                v[j] = v[j + 1]
                v[j + 1] = aux
        if i % steps == 0:
            print(i, ". : ", v)
    print(v)


def comb_sort(v):
    l = len(v)
    # l is the length of the array
    gap = l
    j = 0
    steps = int(input("Enter steps: "))
    while gap != 1:

        gap = (gap * 10) // 13
        for i in range(0, l - gap):
            if v[i] > v[i + gap]:
                aux = v[i]
                v[i] = v[i + gap]
                v[i + gap] = aux
            j = j + 1
            if j % steps == 0:
                print(j, ". : ", v)
    print(v)


def menu():
    print("[1] Generate Random List")
    print("[2] Bubble Sort the List")
    print("[3] Comb Sort the List")
    print("[0] Exit Menu")
    print("* must always generate a random list before choosing a sorting algorithm *")


if __name__ == "__main__":
    menu()
    option = int(input("Enter your option: "))
    # The user must always generate a random list before sorting it
    while option != 0:
        if option == 1:
            print()
            v = []
            max_length = int(input("Enter length: "))
            for i in range(0, max_length):
                v.append(random.randint(0, 100))
            print(v)
        elif option == 2:
            print()
            print("Bubble sort:")
            bubble_sort(v)
        elif option == 3:
            print()
            print("Comb sort:")
            comb_sort(v)
        print()
        menu()
        option = int(input("Enter your option: "))
    print()
    print("Menu exited successfully")
