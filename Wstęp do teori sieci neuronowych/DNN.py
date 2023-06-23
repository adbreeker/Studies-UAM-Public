import math

beta = 3.0
w = [[0.0,1.0,2.0],[0.0,1.0,2.0]]
s = [0.0,1.0,2.0]
u1 = [0,0,1]
u2 = [1,0,1]
u3 = [0,1,1]
u4 = [1,1,1]
u = [u1,u2,u3,u4]

def f(x) -> float:
    return 1/(1+math.exp(-beta*x))

def x1(p):
    sum = 0
    for j in range(3):
        sum += w[0][j] * u[p-1][j]

    return f(sum)


def x2(p):
    sum = 0
    for j in range(3):
        sum += w[1][j] * u[p-1][j]

    return f(sum)

def x3(p):
    return 1.0


def y(p):
    x = [x1(p),x2(p),x3(p)]
    sum = 0
    for i in range(3):
        sum += s[i]*x[i]

    return f(sum)
    

print(y(1))
print(y(2))
print(y(3))
print(y(4))