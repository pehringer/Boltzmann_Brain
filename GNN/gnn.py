import random
import math
import time




def gnn_functions(fn: str) -> any:
	f = lambda z : z
	match fn.lower():
		case "tanh":
			f = lambda z : math.tanh(z)
	return f




def gnn_initalize(L: int, N: list) -> tuple[dict, dict]:
	b = {}
	w = {}
	for l in range(1, L):
		for j in range(0, N[l]):
			b[(l,j)] = random.uniform(-1.0, 1.0)
			for i in range(0, N[l-1]):
				w[(l,i,j)] = random.uniform(-1.0, 1.0)
	return b, w




def gnn_forward_propagate(b: dict, bm: dict, f: any, L: int, N: list, w: dict, wm: dict, x: list) -> list:
	a = {}
	z = {}
	for i in range(0, N[0]):
		a[(0,i)] = x[i]
	for l in range(1, L):
		for j in range(0, N[l]):
			if (l,j) in bm:
				z[(l,j)] = bm[(l,j)]
			else:
				z[(l,j)] = b[(l,j)]
			for i in range(0, N[l-1]):
				if (l,i,j) in wm:
					z[(l,j)] += wm[(l,i,j)] * a[(l-1,i)]
				else:
					z[(l,j)] += w[(l,i,j)] * a[(l-1,i)]
			a[(l,j)] = f(z[(l,j)])
	y = [0.0] * N[L-1]
	for i in range(0, N[L-1]):
		y[i] = a[(L-1,i)]
	return y




def gnn_mutate(bm: dict, s: int, wm: dict) -> list:
	p = [(0.0, bm, wm)]
	for i in range(s):
		bmi = {}
		for k, v in bm.items():
			if(random.random() < 0.5):
				v += random.uniform(-0.2, 0.2)
			bmi[k] = v
		wmi = {}
		for k, v in wm.items():
			if(random.random() < 0.5):
				v += random.uniform(-0.2, 0.2)
			wmi[k] = v
		p.append((0.0, bmi, wmi))
	return p




def gnn_fitness(b: dict, f: any, L: int, N: list, p: list, t: list, w: dict) -> list:
	for k in range(len(p)):
		_, bm, wm = p[k]
		e = 0.0
		for x, yt in t:
			y = gnn_forward_propagate(b, bm, f, L, N, w, wm, x)
			for i, j in zip(yt, y):
				e += abs(i - j)
		p[k] = (e, bm, wm)
	return p




def gnn_select(p: list) -> tuple[float, dict, dict]:
	p.sort(key=lambda a: a[0])
	e, bm, wm = p[0]
	return e, bm, wm




def gnn_train(b: dict, f: any, L: int, N: list, t: list, w: dict) -> tuple[dict, dict]:
	bm = {}
	wm = {}
	i = random.randrange(0, N[0])
	for l in range(1, L):
		j = random.randrange(0, N[l])
		bm[(l,j)] = b[(l,j)]
		wm[(l,i,j)] = w[(l,i,j)]
		i = j
	s = (len(bm) + len(wm)) * 5
	for i in range(s):
		p = gnn_mutate(bm, s, wm)
		p = gnn_fitness(b, f, L, N, p, t, w)
		e, bm, wm = gnn_select(p)
	print(e)
	for k, v in bm.items():
		b[k] = v
	for k, v in wm.items():
		w[k] = v
	return b, w




L = 3
N = [2, 2, 1]
t = [
	([0.0, 0.0], [0.0]),
	([0.0, 1.0], [0.0]),
	([1.0, 0.0], [0.0]),
	([1.0, 1.0], [1.0]),
]
f = gnn_functions("Tanh")
b, w = gnn_initalize(L, N)
for e in range(128):
	b, w = gnn_train(b, f, L, N, t, w)
for x, yt in t:
	y = gnn_forward_propagate(b, {}, f, L, N, w, {}, x)
	print(x, y, yt)
