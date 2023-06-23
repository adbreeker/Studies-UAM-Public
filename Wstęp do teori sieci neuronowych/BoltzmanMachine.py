from random import randint
import math
import random


x_s = [0, 0, 0, 0, 0,
       0, 1, 1, 0, 0,
       0, 0, 1, 0, 0,
       0, 0, 1, 0, 0,
       0, 0, 1, 0, 0]

T = 2.5

def create_c():
    c_a = []
    for p in range(25):
        tmp = []
        for q in range(25):
            tmp.append((x_s[p] - 0.5) * (x_s[q] - 0.5))
        c_a.append(tmp)
    for idx in range(25):
        c_a[idx][idx] = 0
    return c_a


def thetas():
    ch = create_c()
    theta = []
    for d in range(25):
        sum = 0
        for g in range(25):
            sum += ch[d][g]
        theta.append(sum)
    return theta


def w_a():
    w_x = create_c()
    for a in range(25):
        for b in range(25):
            w_x[a][b] = w_x[a][b] * 2
    return w_x


def u():
    _u = []
    theta = thetas()
    w_i = w_a()
    for _i in range(25):
        _sum = 0
        for _j in range(25):
            _sum += w_i[_i][_j] * x[_j]
        _sum -= theta[_i]
        _u.append(_sum)
    return _u

def f(ui,T):
    return 1 / (1+math.exp((-ui)/T))

w = [[]]
x = []
t = 0
for i in range(25):
    x.append(randint(0, 1))

for z in range(100):
    print(z, end=": \n")
    for i in range(5):
        s = ""
        for j in range(5):
            if x[5 * i + j] == 1:
                s += "0"
            if x[5 * i + j] == 0:
                s += "1"
        print(s)

    print(" ")
    t += 1
    u_i = u()
    for i in range(25):
        beta = random.random()
        if 0 <= beta <= f(u_i[i], T):
            x[i] = 1
        if f(u_i[i],T) <= beta <= 1:
            x[i] = 0

    input()
