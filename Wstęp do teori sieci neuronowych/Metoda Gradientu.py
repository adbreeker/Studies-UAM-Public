import random

def DX1x1(x1, x2):
    return 4 * x1 - 2 * x2 - 2


def DX1x2(x1, x2, x3):
    return 4 * x2 - 2 * x1 - 2 * x3


def DX1x3(x2, x3):
    return 2 * x3 - 2 * x2


def DX2x1(x1, x2):
    return 12 * (x1 ** 3) + 12 * (x1 ** 2) - 24 * x1


def DX2x2(x1, x2):
    return 24 * x2 - 24


def F1(x1, x2, x3):
    return 2 * (x1 ** 2) + 2 * (x2 ** 2) + (x3 ** 2) - 2 * x1 * x2 - 2 * x2 * x3 - 2 * x1 + 3


def F2(x1, x2):
    return 3 * (x1 ** 4) + 4 * (x1 ** 3) - 12 * (x1 ** 2) + 12 * (x2 ** 2) - 24 * x2

#3 * (x1 * 4) + 4 * (x1 * 3) - 12 * (x1 * 2) + 12 * (x2 * 2) - 24 * x2

c = 0.001
epsilon = 0.00001
N = 50

x_old_array = [((random.uniform(-N,N) / N*0.5) -0.5) * 2 * N for i in range(3)]
x_new_array = [0, 0, 0]
print(f'x_old = {x_old_array}')

tmp = [0, 0, 0]
for index in range(3):
    tmp[index] = x_new_array[index] - x_old_array[index]
x_new_array[0] = x_old_array[0] - c * DX1x1(x_old_array[0], x_old_array[1])
x_new_array[1] = x_old_array[1] - c * DX1x2(x_old_array[0], x_old_array[1], x_old_array[2])
x_new_array[2] = x_old_array[2] - c * DX1x3(x_old_array[1], x_old_array[2])


# print(f'tmp = {tmp}')
# print(f'x_new = {x_new_array}')


index = 0
while max(tmp) > epsilon:
    x_old_array[index] = x_new_array[index]
    x_new_array[index] = x_old_array[index] - c * DX1x1(x_old_array[0], x_old_array[1])

    x_old_array[index + 1] = x_new_array[index + 1]
    x_new_array[index + 1] = x_old_array[index + 1] - c * DX1x2(x_old_array[0], x_old_array[1], x_old_array[2])

    x_old_array[index + 2] = x_new_array[index + 2]

    x_new_array[index + 2] = x_old_array[index + 2] - c * DX1x3(x_old_array[1], x_old_array[2])

    tmp = [0, 0, 0]
    for i in range(3):
        tmp[i] = x_new_array[i] - x_old_array[i]

    index = 0

print(x_new_array[0], x_new_array[1], x_new_array[2])
print(F2(x_new_array[0], x_new_array[1]))
