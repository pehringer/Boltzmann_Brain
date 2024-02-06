import random
import math

'''________________________________
   Feed Forward Neural Network Code
   --------------------------------'''

def ffnn_function(fn: str) -> any:
        f = lambda z : z
        match fn.lower():
                case "tanh":
                        f = lambda z : math.tanh(z)
                case "relu":
                        f = lambda z : max(0.0, z)
        return f

def ffnn_initalize(L: int, N: list) -> tuple[dict, dict]:
        b = {}
        w = {}
        for l in range(1, L):
                for j in range(0, N[l]):
                        b[(l,j)] = random.uniform(-0.1, 0.1)
                        for i in range(0, N[l-1]):
                                w[(l,i,j)] = random.uniform(-0.1, 0.1)
        return b, w

def ffnn_propagate(b: dict, bo: dict, f: any, L: int, N: list, w: dict, wo: dict, x: list) -> list:
        a = {}
	z = {}
	for i in range(0, N[0]):
                a[(0,i)] = x[i]
        for l in range(1, L):
                for j in range(0, N[l]):
                        if (l,j) in bo:
                                z[(l,j)] = bo[(l,j)]
                        else:
                             	z[(l,j)] = b[(l,j)]
                        for i in range(0, N[l-1]):
                                if (l,i,j) in wo:
                                        z[(l,j)] += wo[(l,i,j)] * a[(l-1,i)]
                                else:
                                     	z[(l,j)] += w[(l,i,j)] * a[(l-1,i)]
                        a[(l,j)] = f(z[(l,j)])
        y = [0.0] * N[L-1]
        for i in range(0, N[L-1]):
                y[i] = a[(L-1,i)]
        return y

'''_______________________
   Genectic Algorithm Code
   -----------------------'''

def gnn_feature(b: dict, L: int, N: list, w: dict) -> tuple[dict, dict]:
        fb = {}
        fw = {}
        i = random.randrange(0, N[0])
        for l in range(1, L):
                j = random.randrange(0, N[l])
                fw[(l,i,j)] = w[(l,i,j)]
                fb[(l,j)] = b[(l,j)]
                i = j
        return fb, fw

def gnn_fitness(b: dict, mb: dict, f: any, L: int, N: list, t: list, w: dict, mw: dict) -> float:
        e = 0.0
        for x, yt in t:
                y = ffnn_propagate(b, mb, f, L, N, w, mw, x)
                for i, j in zip(yt, y):
                        e += abs(i - j)
        return e

def gnn_train(b: dict, f: any, L: int, N: list, t: list, w: dict) -> tuple[float, dict, dict]:
        fb, fw = gnn_feature(b, L, N, w)
        fe = gnn_fitness(b, {}, f, L, N, t, w, {})
        for p in range(64):
                mb = {}
                mw = {}
                for k, v in fb.items():
                        if random.random() < 0.25:
                                v += random.uniform(-0.1, 0.1)
                        mb[k] = v
                for k, v in fw.items():
                        if random.random() < 0.25:
                                v += random.uniform(-0.1, 0.1)
                        mw[k] = v
                me = gnn_fitness(b, mb, f, L, N, t, w, mw)
                if me < fe:
                        fe = me
                        fb = mb
                        fw = mw
        for k, v in fb.items():
                b[k] = v
        for k, v in fw.items():
                w[k] = v
        return fe, b, w

'''_____________
   Training Code
   -------------'''

t_not = [
([0.0], [1.0]),
([1.0], [0.0]),
]


t_and = [
([0.0, 0.0], [0.0]),
([0.0, 1.0], [0.0]),
([1.0, 0.0], [0.0]),
([1.0, 1.0], [1.0]),
]

t_nand = [
([0.0, 0.0], [1.0]),
([0.0, 1.0], [1.0]),
([1.0, 0.0], [1.0]),
([1.0, 1.0], [0.0]),
]

t_or = [
([0.0, 0.0], [0.0]),
([0.0, 1.0], [1.0]),
([1.0, 0.0], [1.0]),
([1.0, 1.0], [1.0]),
]

t_nor = [
([0.0, 0.0], [1.0]),
([0.0, 1.0], [0.0]),
([1.0, 0.0], [0.0]),
([1.0, 1.0], [0.0]),
]

t_xor = [
([0.0, 0.0], [0.0]),
([0.0, 1.0], [1.0]),
([1.0, 0.0], [1.0]),
([1.0, 1.0], [0.0]),
]

t_full_adder = [
([0.0, 0.0, 0.0], [0.0, 0.0]),
([0.0, 0.0, 1.0], [1.0, 0.0]),
([0.0, 1.0, 0.0], [1.0, 0.0]),
([0.0, 1.0, 1.0], [0.0, 1.0]),
([1.0, 0.0, 0.0], [1.0, 0.0]),
([1.0, 0.0, 1.0], [0.0, 1.0]),
([1.0, 1.0, 0.0], [0.0, 1.0]),
([1.0, 1.0, 1.0], [1.0, 1.0]),
]

t = t_full_adder
f = ffnn_function("relu")
L = 5
N = [3, 16, 16, 16, 2]

b, w = ffnn_initalize(L, N)
for c in range(4096):
        e, b, w = gnn_train(b, f, L, N, t, w)
        print(c, e)

for x, yt in t:
        y = ffnn_propagate(b, {}, f, L, N, w, {}, x)
        print(yt, y)
