from decimal import *

epsA = Decimal()
epsB = Decimal()
epsC = Decimal()
A = [[]]
idn = []
idm = []
n = 0
m = 0


def pivot(l, e):
    idm[l], idn[e] = idn[e], idm[l]
    fac = A[l][e]
    A[l][e] = Decimal(1)
    que = []
    for i in range(n+1):
        A[l][i] /= fac
        if A[l][i] < -epsC or A[l][i] > epsC:
            que.append(i)
    for i in range(m+1):
        if i != l:
            k = A[i][e]
            A[i][e] = Decimal(0)
            if -epsC < k and k < epsC:
                continue
            for j in que:
                A[i][j] -= k * A[l][j]


def init():
    while True:
        l = -1
        for i in range(m):
            if A[i][n] < -epsA and idm[i] < idm[l]:
                l = i
        if l == -1:
            return True
        e = -1
        for i in range(n):
            if A[l][i] < -epsA and idn[i] < idn[e]:
                e = i
        if e == -1:
            return False
        pivot(l, e)


def simplex():
    if not init():
        print("Infeasible")
        return False

    while True:
        e = -1
        for i in range(n):
            if A[m][i] > epsB and idn[i] < idn[e]:
                e = i
        if e == -1:
            return True
        minv = Decimal(0)
        l = -1
        for i in range(m):
            if A[i][e] > epsB:
                val = A[i][n] / A[i][e]
                if (l == -1 or val < minv
                    or (Decimal.copy_abs(val - minv) < epsC
                        and idm[i] < idm[l])):
                    minv = val
                    l = i
        if l == -1:
            print("Unbounded")
            return False
        pivot(l, e)


def toString(val):
    return Decimal(val).quantize(Decimal('0.00000000'))


def mainImpl():
    getcontext().prec = 80

    global epsA
    epsA = Decimal.from_float(1e-20)
    global epsB
    epsB = Decimal.from_float(1e-30)
    global epsC
    epsC = Decimal.from_float(1e-40)

    global n
    global m
    n, m, t = map(int, input().split())

    tmp = [Decimal(i) for i in input().split()] + [0]

    global A
    A = [[] for i in range(m)]
    for i in range(m):
        A[i] = [Decimal(i) for i in input().split()]
    A.append(tmp)

    inf = 1 << 30
    global idn
    idn = [i for i in range(n)]+[inf]
    global idm
    idm = [n+i for i in range(m)]+[inf]

    if simplex():
        print(toString(-A[m][n]))

        if t == 1:
            ans = [Decimal('0.0') for i in range(n+m+5)]
            for i in range(m):
                ans[idm[i]] = A[i][n]
            for i in range(n):
                print(toString(ans[i]), end=' ')
            print()


if __name__ == '__main__':
    try:
        mainImpl()
    except Exception as err:
        print("Exception:{0}".format(err))
