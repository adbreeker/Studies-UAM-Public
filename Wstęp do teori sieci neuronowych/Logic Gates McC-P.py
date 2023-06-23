def f(x): #funkcja progowa
    if x < 0:
        return 0
    else:
        return 1


def AND(x1, x2):
    w = [2, 2, -3]
    u = [x1, x2, 1]
    y = f(sum([w[i] * u[i] for i in range(len(w))]))
    return y


def NOT(x):
    w = [-2, 1]
    u = [x, 1]
    y = f(sum([w[i] * u[i] for i in range(len(w))]))
    return y


def NAND(x1, x2):
    w = [-2, -2, 3]
    u = [x1, x2, 1]
    y = f(sum([w[i] * u[i] for i in range(len(w))]))
    return y


def OR(x1, x2):
    w = [2.0, 2.0, -1.0]
    u = [x1, x2, 1]
    y = f(sum([w[i] * u[i] for i in range(len(w))]))
    return y


print("NOT:")
print(NOT(0))  # 1
print(NOT(1))  # 0
print("AND:")
print(AND(0, 0))  # 0
print(AND(1, 0))  # 0
print(AND(0, 1))  # 0
print(AND(1, 1))  # 1
print("NAND:")
print(NAND(0, 0))  # 1
print(NAND(1, 0))  # 1
print(NAND(0, 1))  # 1
print(NAND(1, 1))  # 0
print("OR:")
print(OR(0, 0))  # 0
print(OR(1, 0))  # 1
print(OR(0, 1))  # 1
print(OR(1, 1))  # 1