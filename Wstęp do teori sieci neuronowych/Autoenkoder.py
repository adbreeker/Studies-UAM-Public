import math

beta = 3.0
w = [[20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -10.0],
     [0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -10.0]]

u1 = [1,1,0,
      0,1,0,
      0,1,0,1]

u2 = [0,0,1,
      0,0,1,
      0,0,1,1]

u = [u1,u2]

def f(x) -> float:
    return 1/(1+math.exp(-beta*x))

def x1(p):
    sum = 0
    for j in range(10):
        sum += w[0][j] * u[p-1][j]

    return f(sum)


def x2(p):
    sum = 0
    for j in range(10):
        sum += w[1][j] * u[p-1][j]

    return f(sum)

def x3(p):
    return 1.0

def s(j,i):
    if i == 2:
        return -10.0
    else:
        return 20*u[i][j-1]


def y(j,p):
    x = [x1(p),x2(p),x3(p)]
    sum = 0
    for i in range(3):
        sum += s(j,i)*x[i]

    return f(sum)

print('\n')  

print(f'{y(1,1)} {y(2,1)} {y(3,1)}')
print(f'{y(4,1)} {y(5,1)} {y(6,1)}')
print(f'{y(7,1)} {y(8,1)} {y(9,1)}')

print('\n')

print(f'{y(1,2)} {y(2,2)} {y(3,2)}')
print(f'{y(4,2)} {y(5,2)} {y(6,2)}')
print(f'{y(7,2)} {y(8,2)} {y(9,2)}')

print('\n')

