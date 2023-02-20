"""
6.Given an array of integers A, maximize the value of the expression A[m] - A[n] + A[p] - A[q],
where m, n, p, q are array indices with m > n > p > q. For A = [30, 5, 15, 18, 30, 40],
the maximum value is 32, obtained as 40 - 18 + 15 - 5 = 22 + 10 = 32
Display both the maximum value as well as the expression used to calculate it.
"""
import sys


def naive_equation(a):
    vm = vn = vp = vq = 0
    maximal_value = 0
    for m in range(0, len(a)):
        for n in range(0, m):
            for p in range(0, n):
                for q in range(0, p):
                    result = a[m] - a[n] + a[p] - a[q]
                    if result >= maximal_value:
                        maximal_value = result
                        vm = a[m]
                        vn = a[n]
                        vp = a[p]
                        vq = a[q]
    print(f"{vm}-{vn}+{vp}-{vq}={maximal_value}")


def dynamic_equation(a):
    if len(a) < 4:
        print("The length of the array is too short! Enter more numbers!")
        exit(0)
    first = [-sys.maxsize] * (len(a) + 1)
    second = [-sys.maxsize] * len(a)
    third = [-sys.maxsize] * (len(a) - 1)
    fourth = [-sys.maxsize] * (len(a) - 2)
    for i in reversed(range(len(a))):
        first[i] = max(first[i + 1], a[i])
    for i in reversed(range(len(a) - 1)):
        second[i] = max(second[i + 1], first[i + 1] - a[i])
    for i in reversed(range(len(a) - 2)):
        third[i] = max(third[i + 1], second[i + 1] + a[i])
    for i in reversed(range(len(a) - 3)):
        fourth[i] = max(fourth[i + 1], third[i + 1] - a[i])
    vm = first[0]
    vn = first[0] - second[3]
    vp = third[0] - second[4] - first[0]
    vq = third[1] - fourth[1]
    print(f"{vm}-{vn}+{vp}-{vq}={fourth[0]}")


if __name__ == "__main__":
    print("The naive method: ")
    naive_equation([30, 5, 15, 18, 30, 40])
    print()
    print("The dynamic method: ")
    dynamic_equation([30, 5, 15, 18, 30, 40])
