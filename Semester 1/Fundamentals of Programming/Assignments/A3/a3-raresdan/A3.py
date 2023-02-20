# I was assigned: Bubble Sort & Comb Sort
import copy
import random
import time


def generate_random_list(l):
    v = []
    for i in range(0, l):
        v.append(random.randint(0, 100))
    return v


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


# functions without the 'steps' option

def time_of_bubble_sort(v):
    l = len(v)
    # l is the length of the array
    for i in range(0, l):
        swap = False
        for j in range(0, l - i - 1):
            if v[j] > v[j + 1]:
                aux = v[j]
                v[j] = v[j + 1]
                v[j + 1] = aux
                swap = True
        if not swap:
            break
    return v


def time_of_comb_sort(v):
    l = len(v)
    # l is the length of the array
    gap = l
    while gap != 1:
        gap = (gap * 10) // 13
        for i in range(0, l - gap):
            if v[i] > v[i + gap]:
                aux = v[i]
                v[i] = v[i + gap]
                v[i + gap] = aux
    return v


def time_of_execution(function, v):
    start = time.time()
    function(v)
    stop = time.time()
    return round((stop - start) * 1000, 5)


def menu():
    print("[1] Generate Random List")
    print("[2] Bubble Sort the List")
    print("[3] Comb Sort the List")
    print("[4] Worst Case")
    print("[5] Best Case")
    print("[6] Average Case")
    print("[0] Exit Menu")
    print("* must always generate a random list before choosing a sorting algorithm *")


def call_menu():
    v = []
    while True:
        option = 1
        while True:
            try:
                print()
                option = int(input("Enter your option: "))
                break
            except ValueError:
                print("Error! Invalid option!")
            if 0 > option > 6:
                print("Error! Invalid option!")
        # Choosing Options
        if option == 1:
            print()
            v = []
            while True:
                try:
                    l = int(input("Enter the length: "))
                    break
                except ValueError:
                    print("Error! Invalid length!")
            while l > 0:
                v.append(random.randint(1, 100))
                l = l - 1
            print(v)
        elif 1 < option < 4:
            if len(v) == 0:
                print("There is no list to be sorted!")
            else:
                if option == 2:
                    print()
                    print("Bubble sort:")
                    bubble_sort(v)
                else:
                    print()
                    print("Comb sort:")
                    comb_sort(v)
        elif 3 < option < 7:
            while True:
                try:
                    max_length = int(input("Enter length: "))
                    break
                except ValueError:
                    print("Error! Invalid length!")
            bubble_time = []
            comb_time = []
            if option == 4:
                print()
                print("Worst Case was chosen")
                for i in range(5):
                    v = generate_random_list(max_length)
                    v.sort(reverse=True)
                    list_bubble = copy.deepcopy(v)
                    list_comb = copy.deepcopy(v)
                    bubble_time.append(time_of_execution(time_of_bubble_sort, list_bubble))
                    comb_time.append(time_of_execution(time_of_comb_sort, list_comb))
                    max_length = max_length * 2
            elif option == 5:
                print()
                print("Best Case was chosen")
                for i in range(5):
                    v = generate_random_list(max_length)
                    v.sort()
                    list_bubble = copy.deepcopy(v)
                    list_comb = copy.deepcopy(v)
                    bubble_time.append(time_of_execution(time_of_bubble_sort, list_bubble))
                    comb_time.append(time_of_execution(time_of_comb_sort, list_comb))
                    max_length = max_length * 2
            elif option == 6:
                print()
                print("Average Case was chosen")
                for i in range(5):
                    v = generate_random_list(max_length)
                    list_bubble = copy.deepcopy(v)
                    list_comb = copy.deepcopy(v)
                    bubble_time.append(time_of_execution(time_of_bubble_sort, list_bubble))
                    comb_time.append(time_of_execution(time_of_comb_sort, list_comb))
                    max_length = max_length * 2
            print(f"Bubble Sort results: {bubble_time}")
            print(f"Comb Sort results: {comb_time}")
        if option == 0:
            print()
            print("Menu exited successfully")
            break


if __name__ == "__main__":
    menu()
    call_menu()

"""
Bubble Sort Complexity:
This algorithm has a worst-case time complexity of O(n2). 

Comb Sort Complexity:
Time Complexity: O(n log n) for the best case.
                 O(n^2) for the worst case
"""