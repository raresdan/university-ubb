def complexity_1(x):
    m = len(x)
    found = False
    while m >= 1:
        c = m - m / 3 * 3
        if c == 1:
            found = True
            m = m / 3


def complexity_2(x):
    found = False
    n = len(x) - 1
    while n != 0 and not found:
        if x[n] == 7:
            found = True
        else:
            n = n - 1
    return found


def complexity_3(n, i):
    if n > 1:
        i *= 2
        m = n // 2
        complexity_3(m, i - 2)
        complexity_3(m, i - 1)
        complexity_3(m, i + 2)
        complexity_3(m, i + 1)
    else:
        print(i)


print(complexity_2([7, 8]))
print(complexity_3(5, 4))
