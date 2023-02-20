#
# Write the implementation for A5 in this file
#

from functionalities import *


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def menu():
    print("----------------------MENU--------------------------")
    print("Type the number associated with the task you want to execute")
    print("The list already contains 10 random complex numbers")
    print()
    print("[1] Add one or more written complex numbers to the list")
    print("[2] Add one or more random complex numbers to the list")
    print("[3] Display the list")
    print("[4] Display the longest subarray where their real and imaginary parts can be written using the same digits ")
    print("[5] Display the list of modules of the complex numbers")
    print("[6] Display the longest increasing subsequence considering each number's modulus")
    print("[7] Clear the list")
    print("[0] Exit Menu")


def start():
    menu()
    complex_list_strings = []
    complex_list = []
    for _ in range(0, 10):
        z = generate_random()
        complex_list.append(z)
        complex_list_strings.append(to_str(z))
    print()
    print("Your initial list is:")
    print(complex_list_strings)
    while True:
        option = 1
        while True:
            try:
                print()
                option = int(input("Enter your option: "))
                print()
                break
            except ValueError:
                print("Error! Invalid option!")
            if 0 > option > 8:
                print("Error! Invalid option!")
        if option == 1:
            while True:
                try:
                    i = int(input("How many complex numbers do you want to add to the list? "))
                    print()
                    break
                except ValueError:
                    print("Error! Invalid value!")
            while i > 0:
                while True:
                    try:
                        re = int(input("Give real part: "))
                        img = int(input("Give imaginary part: "))
                        break
                    except ValueError:
                        print("Error! Invalid values!")
                z = create_complex(re, img)
                print()
                print(f"{to_str(z)} was created!")
                print()
                complex_list_strings.append(to_str(z))
                complex_list.append(z)
                print(f"{to_str(z)} was added to the list!")
                print()
                i = i - 1
            print("The list you created is: ")
            print(complex_list_strings)
        elif 1 < option < 8:
            if option == 2:
                while True:
                    try:
                        i = int(input("How many complex numbers do you want to add to the list? "))
                        print()
                        break
                    except ValueError:
                        print("Error! Invalid value!")
                while i > 0:
                    z = generate_random()
                    complex_list_strings.append(to_str(z))
                    complex_list.append(z)
                    print(f"{to_str(z)} was added to the list!")
                    print()
                    i = i - 1
                print("The list you created is: ")
                print(complex_list_strings)
            if option == 3:
                print("Your current list is: ")
                print(complex_list_strings)
            elif option == 4:
                n = len(complex_list)
                length = len_longest_subarray(complex_list, n)
                print(f"The length of the longest subarray is {length} ")
                print()
                subarray = return_longest_subarray(complex_list, n)
                print(f"The longest subarray is {subarray}")
            elif option == 5:
                modules = modules_list(complex_list)
                print(f"The  list of modules of the complex numbers is {modules}")
            elif option == 6:
                result = longest_increasing_subsequence(complex_list)
                print(f"the longest increasing subsequence is : {result}")
                print()
                print(f"The length of the longest increasing subsequence is {len(result)} ")
            elif option == 7:
                complex_list_strings = []
                complex_list = []
                print("The list was cleared and it is empty now!")
        if option == 0:
            print("Menu exited successfully")
            break
        print()


if __name__ == "__main__":
    print("Make magic happen")
    start()
