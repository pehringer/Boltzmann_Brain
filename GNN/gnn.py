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
			b[(l,j)] = random.uniform(-1.0, 1.0)
			for i in range(0, N[l-1]):
				w[(l,i,j)] = random.uniform(-1.0, 1.0)
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

def gnn_feature(b: dict, L: int, N: list, P: int, w: dict) -> tuple[dict, dict]:
	fb = {}
	fw = {}
	# Select neuron and copy bias.
	l = random.randrange(1, L)
	j = random.randrange(0, N[l])
	if P > 0:
		fb[(l,j)] = b[(l,j)]
	# Compute weight range.
	s = 0
	e = N[l-1]
	if e - P + 1 > 0:
		s = random.randint(0, e - P + 1)
		e = s + P - 1
	# Copy  weights.
	while s < e:
		i = s
		fw[(l,s,j)] = w[(l,i,j)]
		s += 1
	return fb, fw

def gnn_pathway(b: dict, L: int, N: list, P: int, w: dict) -> tuple[dict, dict]:
	pb = {}
	pw = {}
	# Compute layer range.
	s = 2
	e = L * 2
	if e - P > 2:
		s = random.randint(2, e - P)
		e = s + P
	# Select starting point.
	l = s // 2
	i = random.randrange(0, N[l-1])
	# Select and copy parameters.
	while s < e:
		l = s // 2
		j = random.randrange(0, N[l])
		if s % 2 == 0 and s < e:
			pw[(l,i,j)] = w[(l,i,j)]
			s += 1
		if s % 2 == 1 and s < e:
			pb[(l,j)] = b[(l,j)]
			s += 1
		i = j
	return pb, pw

def gnn_mutate(bo: dict, s: int, wo: dict) -> list:
	p = [(0.0, bo, wo)]
	for i in range(s):
		boi = {}
		for k, v in bo.items():
			if random.random() < 0.5:
				v += random.uniform(-0.2, 0.2)
			boi[k] = v
		woi = {}
		for k, v in wo.items():
			if random.random() < 0.5:
				v += random.uniform(-0.2, 0.2)
			woi[k] = v
		p.append((0.0, boi, woi))
	return p

def gnn_fitness(b: dict, f: any, L: int, N: list, p: list, t: list, w: dict) -> list:
	for k in range(len(p)):
		_, bo, wo = p[k]
		e = 0.0
		for x, yt in t:
			y = ffnn_propagate(b, bo, f, L, N, w, wo, x)
			for i, j in zip(yt, y):
				e += abs(i - j)
		p[k] = (e, bo, wo)
	return p

def gnn_select(p: list) -> tuple[float, dict, dict]:
	p.sort(key=lambda a: a[0])
	e, bo, wo = p[0]
	return e, bo, wo


def gnn_train(b: dict, bo: dict, f: any, L: int, N: list, t: list, w: dict, wo: dict) -> tuple[float, dict, dict]:
	s = (len(bo) + len(wo)) ** 2
	for i in range(s):
		p = gnn_mutate(bo, s, wo)
		p = gnn_fitness(b, f, L, N, p, t, w)
		e, bo, wo = gnn_select(p)
	for k, v in bo.items():
		b[k] = v
	for k, v in wo.items():
		w[k] = v
	return e, b, w

def gnn_noise(b: dict, w: dict, r: float) -> tuple[dict, dict]:
	for k in b:
		if random.random() < r:
			b[k] = random.uniform(-1.0, 1.0)
	for k in w:
		if random.random() < r:
			w[k] = random.uniform(-1.0, 1.0)
	return b, w


f = ffnn_function("relu")
L = 3
N = [2, 2, 1]

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

f = ffnn_function("relu")
L = 5
N = [3, 16, 8, 4, 2]

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

'''_________
   Glue Code
   ---------'''

t = t_full_adder
b, w = ffnn_initalize(L, N)
for c in range(64):
	bo, wo = gnn_pathway(b, L, N, 1, w)
	e, b, w = gnn_train(b, bo, f, L, N, t, w, wo)
	bo, wo = gnn_pathway(b, L, N, 2, w)
	e, b, w = gnn_train(b, bo, f, L, N, t, w, wo)
	bo, wo = gnn_pathway(b, L, N, 3, w)
	e, b, w = gnn_train(b, bo, f, L, N, t, w, wo)
	bo, wo = gnn_pathway(b, L, N, 4, w)
	e, b, w = gnn_train(b, bo, f, L, N, t, w, wo)
	bo, wo = gnn_pathway(b, L, N, 5, w)
	e, b, w = gnn_train(b, bo, f, L, N, t, w, wo)
	bo, wo = gnn_pathway(b, L, N, 6, w)
	e, b, w = gnn_train(b, bo, f, L, N, t, w, wo)
	print("CYCLE:", c, "ERROR:", e)
	if e > 8:
		b, w = gnn_noise(b, w, 0.06)
	elif e > 7:
		b, w = gnn_noise(b, w, 0.05)
	elif e > 6:
		b, w = gnn_noise(b, w, 0.04)
	elif e > 5:
		b, w = gnn_noise(b, w, 0.03)
	elif e > 4:
		b, w = gnn_noise(b, w, 0.02)
	elif e > 3:
		b, w = gnn_noise(b, w, 0.01)
	elif e > 2:
		b, w = gnn_noise(b, w, 0.005)
