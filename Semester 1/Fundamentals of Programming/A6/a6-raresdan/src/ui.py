#
# This is the program's UI module. The user interface and all interaction with the user
# (print and input statements) are found here
#
import copy

from functions import *


def menu():
    print("----------------------MENU--------------------------")
    print("Type the command associated with the task you want to execute")
    print("The list already has 10 randomly generated transactions")
    print()
    print("Add new transaction")
    print("add <apartment> <type> <amount> - Add to <apartment> an expense for <type> in <amount>")
    print()
    print("Modify expenses")
    print("remove <apartment> - Remove all expenses for <apartment>")
    print("remove <start apartment> to <end apartment> - Remove all expenses for apartments between")
    print("remove <type> - Remove all <type> expenses from all apartments")
    print("replace <apartment> <type> with <amount> - Replace the amount with <type> for <apartment> with <amount>")
    print()
    print("Display expenses having different properties")
    print("list – Display all expenses")
    print("list <apartment> – Display all expenses for <apartment>")
    print("list [ < | = | > ] <amount> – Display all apartments having total expenses < | = | > <amount>")
    print()
    print("Filter")
    print("filter <type> - Keep only expenses for <type>")
    print("filter <value> -  Keep only expenses having an amount of money smaller than <amount>")
    print()
    print("Undo")
    print("undo – The last operation that modified program data is reversed")
    print()
    print("exit - End the application")
    print("----------------------------------------------------")


def print_transactions(transactions_list):
    for i in range(0, len(transactions_list)):
        print(f"#{i + 1} {to_str(transactions_list[i])}")


def start():
    menu()
    transactions_list = []
    generate_initial(transactions_list)
    print()
    print("Your initial transactions are:")
    print_transactions(transactions_list)
    undo_list = []
    copied = copy.deepcopy(transactions_list)
    undo_list.append(copied)
    while True:
        while True:
            try:
                print()
                option = str(input("Enter your option: "))
                print()
                break
            except ValueError:
                print("Error! Invalid option!")
        if option == "exit":
            print("The menu was exited successfully!")
            break
        option_string = option.split()
        if not option_string:
            print("Error! Invalid option!")
        else:
            initial = copy.deepcopy(transactions_list)
            if option_string[0] == "add" and len(option_string) == 4:
                if valid_type(option_string[2]) and option_string[1].isnumeric() and option_string[3].isnumeric():
                    transaction = create_transaction(option_string[1], option_string[3], option_string[2])
                    print(f"{to_str(transaction)} was added")
                    transactions_list.append(transaction)
                    undo_list.append(initial)
                else:
                    print("Invalid types!")
            if option_string[0] == "remove":
                if len(option_string) == 2:
                    if option_string[1].isnumeric():
                        apartment = option_string[1]
                        transactions_list = remove_apartment(transactions_list, apartment)
                        print(f"All expenses for apartment {apartment} were removed")
                        undo_list.append(initial)
                    elif valid_type(option_string[1]):
                        ttype = option_string[1]
                        transactions_list = remove_ttype(transactions_list, ttype)
                        print(f"All {ttype} expenses were removed")
                        undo_list.append(initial)
                    else:
                        print("Invalid command combination!")
                if len(option_string) == 4:
                    if option_string[1].isnumeric() and option_string[3].isnumeric() and option_string[2] == "to":
                        a = option_string[1]
                        b = option_string[3]
                        transactions_list = remove_between(transactions_list, a, b)
                        print(f"All transactions between {a} & {b} were removed")
                        undo_list.append(initial)
                    else:
                        print("Invalid command combination!")
            if option_string[0] == "replace" and len(option_string) == 5 and option_string[3] == "with":
                if valid_type(option_string[2]):
                    apartment = option_string[1]
                    ttype = option_string[2]
                    amount = option_string[4]
                    replace_transaction(transactions_list, apartment, ttype, amount)
                    undo_list.append(initial)
                    print(f"Transaction for {apartment} was replaced!")
                else:
                    print("Invalid command combination!")
            if option_string[0] == "list":
                if len(option_string) == 1:
                    print("Your transactions are:")
                    print_transactions(transactions_list)
                if len(option_string) == 2:
                    if option_string[1].isnumeric():
                        print_transactions(list_apartment(transactions_list, option_string[1]))
                if len(option_string) == 3 and option_string[2].isnumeric() and valid_op(option_string[1]):
                    print_transactions(list_operation(transactions_list, option_string[1], option_string[2]))
                else:
                    print("Invalid command combination!")
            if option_string[0] == "filter" and len(option_string) == 2:
                if valid_type(option_string[1]):
                    transactions_list = filter_ttype(transactions_list, option_string[1])
                    print(f"Transactions were filtered by {option_string[1]}")
                    undo_list.append(initial)
                if option_string[1].isnumeric():
                    transactions_list = filter_operation(transactions_list, option_string[1])
                    print(f"Transactions were filtered by {option_string[1]}")
                    undo_list.append(initial)
            if option_string[0] == "undo":
                if len(undo_list)-1 == 0:
                    print("No operations left to be undone! ")
                else:
                    transactions_list = copy.deepcopy(undo_list.pop())
                    print("The last operation was undone")

