def f(n):
    s = 0
    m = n
    while m != 0:
        s = s + m / 10
        m = m / 10
        print(m)
    return s


def a(n):
    s = 0
    for i in range(1, n + 1):
        m = 2 * i + 1
        s = s + f(m)
    return s


print(a(-5))
