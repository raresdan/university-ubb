# Solve the problem from the second set here
# 11. The numbers `n1` and `n2` have the property `P`
# if their writing in base 10 uses the same digits (e.g. `2113 and 323121`).
# Determine whether two given natural numbers have property `P`.

def frequency(n):
    v = [0] * 10
    while n != 0:
        uc = n % 10
        v[uc] = v[uc] + 1
        n = n // 10
    return v


def p_propriety(n, m):
    a = frequency(n)
    b = frequency(m)
    ok = False
    for i in range(0, 10):
        ok = False
        if (a[i] == 0 and b[i] == 0) or (a[i] != 0 and b[i] != 0):
            ok = True
            if not ok:
                break
    if not ok:
        print("The numbers", n, "and", m, "do not have the P propriety")
    else:
        print("The numbers", n, "and", m, "have the P propriety")


if __name__ == '__main__':
    p_propriety(2113, 323121)
