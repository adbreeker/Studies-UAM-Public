import random

def NWD(a,b):
    while b:
        a,b = b,a%b
    return abs(a)

def solveDL(a,n):
    r = 1
    while a**r % n != 1 and r < 10:
        r+= 1
    if r == 10:
        return -1
    else:
        return 1
    
def factorize(n):
    randomed = random.randint(0, n)

    if NWD(n, randomed) > 1:
        print(f'{n} --- {NWD(n, randomed)}')
    else:
        r = solveDL(randomed, n)
        #print(r)
        if r == -1:
            factorize(n)
        elif r%2 == 0:
            if NWD(n, randomed**(r/2) + 1) > 1:
                print(f'{n} --- {randomed**(r/2) + 1}')
            elif NWD(n, randomed**(r/2) - 1) > 1:
                print(f'{n} --- {randomed**(r/2) - 1}')
            else:
                factorize(n)
        else:
            factorize(n)


factorize(12)
factorize(57)
factorize(91)
factorize(143)
factorize(1859)
factorize(1737)
factorize(13843)
factorize(988027)

