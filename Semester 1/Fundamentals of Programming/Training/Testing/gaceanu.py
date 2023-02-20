a, b = 1, 2
l = [a, b]
a = 7
l2 = [a]
l.append(l2)
l2[0] = 8
print(a, l2, l)


def f(i):
    return i + 1


def g(h):
    return h(1)


def h(x):
    return x + 10


i = lambda x: x + 2
print(f(f(f(g(i)))))


def f():
    return 1


def g(x=1):
    return x + 1


def h(x=1, y=2):
    return x + y


l = [f, g, h]
for e in l:
    print(e())
h = lambda x=1, y=2: x * y
print(l[2](3), h(), h(3), h(x=3), h(y=3))
print(h([2, 3]))
print(h(*[2, 3]))
