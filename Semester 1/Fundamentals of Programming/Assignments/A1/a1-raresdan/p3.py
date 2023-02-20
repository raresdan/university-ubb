# Solve the problem from the third set here
# Solve the problem from the third set here
# 13. Determine the `n-th`  element of the sequence `1,2,3,2,5,2,3,7,2,3,2,5,...`
# obtained from the sequence of natural numbers by replacing composed numbers with
# their prime divisors, without memorizing the elements of the sequence.


def is_prime(n):
    if n == 2:
        return True
    elif n < 2 or n % 2 == 0:
        return False
    for i in range(3, n, 2):
        if n % i == 0:
            return False
    return True


def number_of_divisors(n):
    nd = 0
    for i in range(2, n):
        if is_prime(i) and n % i == 0:
            nd += 1
    return nd


def get_nth_divisor(m, n):
    result = 0
    for i in range(2, m):
        if is_prime(i) and m % i == 0:
            result += 1
            if result == n:
                return i


def the_nth_element_of_the_sequence(n):
    if n == 1:
        return 1
    a = 1
    n = n - 1
    while n != 0:
        a = a + 1
        if is_prime(a):
            n = n - 1
        elif number_of_divisors(a) < n:
            n = n - number_of_divisors(a)
        else:
            return get_nth_divisor(a, n)
    return a


if __name__ == '__main__':
    # print(the_nth_divisor_of_m(1, 9))
    print(the_nth_element_of_the_sequence(n=int(input("Enter the position of the element:"))))
