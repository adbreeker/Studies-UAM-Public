import math
import random

beta = 1.0

def f(x):
    return 1.0 / (1.0 + math.exp(-beta * x))

def d_f(x):
    return (beta * math.exp(-beta * x)) / (math.exp(-beta * x) + 1.0)**2

def calculate_x(w, u):
    x = [[0.0, 0.0, 1.0], [0.0, 0.0, 1.0], [0.0, 0.0, 1.0], [0.0, 0.0, 1.0]]
    for p in range(4):
        x[p][0] = f(w[0][0] * u[p][0] + w[0][1] * u[p][1] + w[0][2] * u[p][2])
        x[p][1] = f(w[1][0] * u[p][0] + w[1][1] * u[p][1] + w[1][2] * u[p][2])
    return x

def calculate_y(s, x):
    y = [0.0, 0.0, 0.0, 0.0]
    for p in range(4):
        y[p] = f(s[0] * x[p][0] + s[1] * x[p][1] + s[2] * x[p][2])
    return y

def calculate_s(s, x, y, z):
    p = random.randrange(4)
    s_new = [0.0, 0.0, 0.0]
    for i in range(3):
        s_new[i] = s_new[i] + (y[p] - z[p]) * d_f(s[0] * x[p][0] + s[1] * x[p][1] + s[2] * x[p][2]) * x[p][i]  
    return s_new

def calculate_w(s, w, u, x, y, z):
    p = random.randrange(4)
    w_new = [[0.0, 0.0, 0.0], [0.0, 0.0, 0.0]]
    vec = [0.0, 0.0, 0.0, 0.0]
    vec[p] = s[0] * x[p][0] + s[1] * x[p][1] + s[2] * x[p][2]
    for i in range(2):
        for j in range(3):
            w_new[i][j] = w_new[i][j] + (y[p] - z[p]) * d_f(vec[p]) * s[i] * d_f(w[i][0] * u[p][0] + w[i][1] * u[p][1] + w[i][2] * u[p][2]) * u[p][j]
    return w_new

def check_max(w_old, w_new, s_old, s_new, eps):
    max_w = 0.0
    max_s = 0.0
    for i in range(2):
        for j in range(3):
            if abs(w_new[i][j] - w_old[i][j]) > max_w:
                max_w = abs(w_new[i][j] - w_old[i][j])
    for j in range(3):
        if abs(s_new[j] - s_old[j]) > max_s:
            max_s = abs(s_new[j] - s_old[j])
    maximum = max(max_w, max_s)
    if maximum < eps:
        return True
    return False

def BP_LOOP(c, eps):
    y = []
    x = []
    s = []
    w = []
    z = [0.0, 1.0, 1.0, 0.0]
    u = [[0, 0, 1], [1, 0, 1], [0, 1, 1], [1, 1, 1]]

    w_old = [[0.0, 1.0, 2.0], [0.0, 1.0, 2.0]]
    s_old = [0.0, 1.0, 2.0]
    w_new = [[0.0, 0.0, 0.0], [0.0, 0.0, 0.0]]
    s_new = [0.0, 0.0, 0.0]
    t = 0

    while True:
        x = calculate_x(w_old, u).copy()
        y = calculate_y(s_old, x).copy()
        s = calculate_s(s_old, x, y, z).copy()
        w = calculate_w(s_old, w_old, u, x, y, z).copy()

        for i in range(3):
            s_new[i] = s_old[i] - c * s[i]

        for i in range(2):
            for j in range(3):
                w_new[i][j] = w_old[i][j] - c * w[i][j]

        if check_max(w_old, w_new, s_old, s_new, eps):
            y = calculate_y(s_old, x)
            break

        s_old = s_new.copy()
        w_old = w_new.copy()
        t = t + 1


    print("\n\nXor output:")
    print("[0, 0]: " + str(round(y[0], 10)))
    print("[1, 0]: " + str(round(y[1], 10)))
    print("[0, 1]: " + str(round(y[2], 10)))
    print("[1, 1]: " + str(round(y[3], 10)))
    print("\n\n")


BP_LOOP(c = 0.5, eps = 0.0001)