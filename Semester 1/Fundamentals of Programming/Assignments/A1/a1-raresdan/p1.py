# Solve the problem from the first set here
# 1. Generate the first prime number larger than a given natural number `n`.

def prime(n):
    if n == 2:
        return True
    if n < 2 or n % 2 == 0:
        return False
    for i in range(3, n // 2 + 1, 2):
        if n % i == 0:
            return False
    return True


def prime_greater_than(n):
    ok = True
    while ok:
        n = n + 1
        if prime(n):
            ok = False
            return n


if __name__ == '__main__':
    print(prime_greater_than(11))
