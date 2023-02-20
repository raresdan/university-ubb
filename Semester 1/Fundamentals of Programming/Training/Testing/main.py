a = 1
b = [str(a), 1]
c = {a: a, str(b[1]): b}
print(type(a))
print(type(c[1]))
print(type(a) == type(c[1]))
a = ['1']
print(type(a))
print(type(c[1]))
print(type(a) == type(c[1]))
print(type(b[0]))
print(type(a))
print(type(b[0]) == type(a))
print(str(a))
print(str(a) in c)
