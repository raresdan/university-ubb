"""
9. The sequence a = a1, ..., an with distinct integer elements is given.
Determine all subsets of at least two elements with the property:
    * The elements in the subset are in increasing order
    * Any two consecutive elements in the subsequence have at least one common digit
"""


def frequency(n):
    v = [0] * 10
    while n != 0:
        uc = n % 10
        v[uc] = v[uc] + 1
        n = n // 10
    return v


def propriety(result):
    if len(result) <= 1:
        return True
    v = frequency(result[-1])
    w = frequency(result[-2])
    for i in range(0, 10):
        if v[i] != 0 and w[i] != 0:
            return True
    return False


def subsets_recursive(numbers):
    numbers.sort()
    result = []
    backtrack(result, [], numbers, 0)
    print(result)


def backtrack(result, temp, numbers, start):
    if len(temp) >= 2:
        result.append(temp[:])
    for i in range(start, len(numbers)):
        temp.append(numbers[i])
        if propriety(temp):
            backtrack(result, temp, numbers, i + 1)
        temp.pop()


def initial_value():
    return -1


def next_value(x):
    if x[-1] == 1:
        return None
    return x[-1] + 1


def is_consistent(x, numbers):
    if len(x) > len(numbers):
        return False
    subset = [numbers[i] for i in range(len(x)) if x[i] == 1]
    if len(x) <= len(numbers) and propriety(subset):
        return True
    return False


def is_solution(x, numbers):
    if len(x) != len(numbers):
        return False
    counter = 0
    for i in range(len(x)):
        counter += x[i]
    return len(x) == len(numbers) and counter >= 2


def print_solution(x, numbers):
    subset = [numbers[i] for i in range(len(x)) if x[i] == 1]
    subset.sort()
    print(subset)


def subsets_iterative(numbers):
    x = [initial_value()]
    while len(x) > 0:
        el = next_value(x)
        while el is not None:
            x[-1] = el
            if is_consistent(x, numbers):
                if is_solution(x, numbers):
                    print_solution(x, numbers)
                else:
                    x.append(initial_value())
                    break
            el = next_value(x)
        if el is None:
            x = x[:-1]
    pass


if __name__ == "__main__":
    print("The result of the recursive backtracking: ")
    subsets_recursive([12, 23, 95, 83, 75])
    print()
    print("The result of the iterative backtracking: ")
    subsets_iterative([12, 23, 95, 83, 75])
