#
# The program's functions are implemented here. There is no user interaction in this file,
# therefore no input/print statements.Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import random


# Functions to define transactions #

def create_transaction(apartment, amount, ttype):
    transaction = dict(apartment=apartment, amount=amount, ttype=ttype)
    return transaction


def get_apartment(transaction: dict):
    return transaction["apartment"]


def get_amount(transaction: dict):
    return transaction["amount"]


def get_ttype(transaction: dict):
    return transaction["ttype"]


def set_apartment(transaction: dict, apartment):
    transaction["apartment"] = apartment


def set_amount(transaction: dict, amount):
    transaction["amount"] = amount


def set_ttype(transaction: dict, ttype):
    transaction["amount"] = ttype


def to_str(transaction: dict):
    return "Apartment: " + str(transaction["apartment"]) + ", " + str(transaction["amount"]) + " RON, " + transaction[
        "ttype"]


def generate_random():
    """
    Generates a random transaction with a defined type and random apartment number and amount
    :return: the randomly generated transaction
    """

    transaction_types = ['water', 'heating', 'electricity', 'gas', 'other']
    apartment = random.randint(1, 100)
    amount = random.randint(1, 1000)
    ttype = random.choice(transaction_types)
    transaction = create_transaction(apartment, amount, ttype)
    return transaction


# Functions to work with the transactions#

def generate_initial(transactions_list: list):
    """
    Generates the initial list of transactions
    :param transactions_list:
    :return: A list with 10 random transactions
    """
    for _ in range(0, 10):
        x = generate_random()
        transactions_list.append(x)
    return transactions_list


def valid_type(ttype):
    """
    Validates if the type introduced by the user exists as a defined type
    :param ttype:
    :return: True if the type exists, False otherwise
    """

    transaction_types = ['water', 'heating', 'electricity', 'gas', 'other']
    if ttype in transaction_types:
        return True
    else:
        return False


def remove_apartment(transaction_list: list, apartment):
    """
    Removes all expenses for a certain apartment
    :param transaction_list:
    :param apartment: The number of the apartment
    :return: The list without the expenses of that certain apartment
    """
    new_list = []
    for i in range(0, len(transaction_list)):
        a = get_apartment(transaction_list[i])
        if int(a) != int(apartment):
            new_list.append(transaction_list[i])
    return new_list


def remove_ttype(transaction_list: list, ttype):
    """
    Removes all expenses for a certain type
    :param transaction_list:
    :param ttype:
    :return: The list without the expenses of that certain type
    """
    new_list = []
    for i in range(0, len(transaction_list)):
        a = get_ttype(transaction_list[i])
        if a != ttype:
            new_list.append(transaction_list[i])
    return new_list


def remove_between(transaction_list: list, a, b):
    """
    Removes the apartments with numbers in [a,b]
    :param transaction_list:
    :param a: first index
    :param b: last index
    :return: The list without the apartments with numbers in [a,b]
    """
    new_list = []
    for i in range(0, len(transaction_list)):
        apartment = get_apartment(transaction_list[i])
        if int(apartment) < int(a):
            new_list.append(transaction_list[i])
        if int(apartment) > int(b):
            new_list.append(transaction_list[i])
    return new_list


def replace_transaction(transaction_list: list, apartment, ttype, amount):
    """
    Replace the amount of the expense with type given and apartment with a wanted amount
    :param transaction_list:
    :param apartment:
    :param ttype:
    :param amount:
    :return: The list with the replaced transaction
    """
    for transaction in transaction_list:
        if int(get_apartment(transaction)) == int(apartment) and get_ttype(transaction) == ttype:
            set_amount(transaction, amount)
            return


def list_apartment(transaction_list: list, apartment):
    """
    List based on apartment number
    :param transaction_list:
    :param apartment:
    :return: The list containing all transactions of that specific apartment
    """
    new_list = []
    for i in range(0, len(transaction_list)):
        a = get_apartment(transaction_list[i])
        if int(a) == int(apartment):
            new_list.append(transaction_list[i])
    return new_list


def valid_op(op):
    """
    Validates if operands entered by user are usable
    :param op:
    :return: True if the operation exists, False otherwise
    """
    operands = ['<', '=', '>']
    if op in operands:
        return True
    else:
        return False


def calculate_expenses(transaction_list: list):
    """
    Calculates the total value of all expenses of an apartment
    :param transaction_list:
    :return:a list containing the total expenses value at the index equal to apartment number
    """
    total = 0
    total_list = [0] * 101
    for i in range(0, len(transaction_list)):
        ap1 = get_apartment(transaction_list[i])
        for j in range(i + 1, len(transaction_list)):
            ap2 = get_apartment(transaction_list[j])
            if ap1 == ap2:
                if total != 0:
                    amount3 = get_amount(transaction_list[j])
                    total += int(amount3)
                    total_list[ap1] = total
                if total == 0:
                    amount1 = get_amount(transaction_list[i])
                    amount2 = get_amount(transaction_list[j])
                    total = int(amount1) + int(amount2)
                    total_list[int(ap1)] = total
                total = 0
            else:
                amount1 = get_amount(transaction_list[i])
                total_list[ap1] = amount1
    ap1 = get_apartment(transaction_list[len(transaction_list) - 1])
    amount1 = get_amount(transaction_list[len(transaction_list) - 1])
    total_list[int(ap1)] = amount1
    return total_list


def list_operation(transaction_list: list, operand, a):
    """
    List based on total value of expenses of each apartment
    :param transaction_list:
    :param operand:
    :param a: the value
    :return:The list containing all transactions of all apartments having total expenses  < | = | > <amount>
    """
    new_list = []
    total_list = calculate_expenses(transaction_list)
    for i in range(0, len(transaction_list)):
        apartment = get_apartment(transaction_list[i])
        total = total_list[apartment]
        if operand == '>':
            if total > int(a):
                new_list.append(transaction_list[i])
        if operand == '=':
            if total == int(a):
                new_list.append(transaction_list[i])
        if operand == '<':
            if total < int(a):
                new_list.append(transaction_list[i])
    return new_list


def filter_ttype(transaction_list: list, ttype):
    """
    Filters based on type
    :param transaction_list:
    :param ttype:
    :return: The list containing all expenses of the wanted type
    """
    new_list = []
    for i in range(0, len(transaction_list)):
        a = get_ttype(transaction_list[i])
        if a == ttype:
            new_list.append(transaction_list[i])
    return new_list


def filter_operation(transaction_list: list, total):
    """
    Filter based on the value of the expenses
    :param transaction_list:
    :param total:
    :return: The list containing all apartments with expenses less than the value
    """
    new_list = []
    total_list = calculate_expenses(transaction_list)
    for i in range(0, len(transaction_list)):
        apartment = get_apartment(transaction_list[i])
        total_ap = total_list[apartment]
        if total_ap < int(total):
            new_list.append(transaction_list[i])
    return new_list


def undo(history):
    history.pop()
    transaction_list = history(len(history) - 1)
    return transaction_list
