import random
import math

def ffnn_functions(fn: str) -> tuple[any, any]:
	f = lambda z : z
	fd = lambda z : z
	match fn.lower():
		case "tanh":
			f = lambda z : math.tanh(z)
			fd = lambda z : 1 - math.tanh(z) ** 2
	return f, fd

def ffnn_initalize(L: int, N: list) -> tuple[dict, dict]:
	b = {}
	w = {}
	for l in range(1, L):
		for j in range(0, N[l]):
			b[(l,j)] = random.random()
			for i in range(0, N[l-1]):
				w[(l,i,j)] = random.random()
	return b, w

def ffnn_forward_propagate(b: dict, f: any, L: int, N: list, w: dict, x: list) -> tuple[dict, list, dict]:
	a = {}
	z = {}
	for i in range(0, N[0]):
		a[(0,i)] = x[i]
	for l in range(1, L):
		for j in range(0, N[l]):
			z[(l,j)] = b[(l,j)] + sum([w[(l,i,j)] * a[(l-1,i)] for i in range(0, N[l-1])])
			a[(l,j)] = f(z[(l,j)])
	y = [0.0] * N[L-1]
	for i in range(0, N[L-1]):
		y[i] = a[(L-1,i)]
	return a, y, z

def ffnn_backward_propagate(a: dict, fd: any, L: int, N: list, yt: list, w: dict, z: dict) -> tuple[dict, dict]:
	d = {}
	for i in range(0, N[L-1]):
		d[(L-1,i)] = fd(z[(L-1,i)]) * (a[(L-1,i)] - yt[i])
	for l in range(L-2, 0, -1):
		for i in range(0, N[l]):
			d[(l,i)] = fd(z[(l,i)]) * sum([w[(l+1,i,j)] * d[(l+1,j)] for j in range(0, N[l+1])])
	db = {}
	dw = {}
	for l in range(1, L):
		for j in range(0, N[l]):
			db[(l,j)] = d[(l,j)]
			for i in range(0, N[l-1]):
				dw[(l,i,j)] = a[(l-1,i)] * d[(l,j)]
	return db, dw

def ffnn_gradient_descent(b: dict, db: dict, L: int, N: list, n: float, w: dict, dw: dict) -> tuple[dict, dict]:
	for l in range(1, L):
		for j in range(0, N[l]):
			b[(l,j)] = b[(l,j)] - n * db[(l,j)]
			for i in range(0, N[l-1]):
				w[(l,i,j)] = w[(l,i,j)] - n * dw[(l,i,j)]
	return b, w

def ffnn_save(b: dict, fn: str, L: int, N: list, w: dict):
	f = open("ffnn.txt", "w")
	f.write("fn" + " " + fn + "\n")
	f.write("L" + " " + str(L) + "\n")
	for n in N:
		f.write("N" + " " + str(n) + "\n")
	for k, v in b.items():
		l, i = k
		f.write("b" + " " + str(l) + " " + str(i) + " " + str(v) + "\n")
	for k, v in w.items():
		l, i, j = k
		f.write("w" + " " + str(l) + " " + str(i) + " " + str(j) + " " + str(v) + "\n")
	f.close()

def ffnn_load() -> tuple[dict, str, int, list, dict]:
	b = {}
	fn = ""
	L = 0
	N = []
	w = {}
	f = open("ffnn.txt", "r")
	for l in f.readlines():
		t = l.split()
		match t[0]:
			case "b":
				b[(int(t[1]), int(t[2]))] = float(t[3])
			case "fn":
				fn = str(t[1])
			case "L":
				L = int(t[1])
			case "N":
				N += [int(t[1])]
			case "w":
				w[(int(t[1]), int(t[2]), int(t[3]))] = float(t[4])
	f.close()
	return b, fn, L, N, w

def ffnn_basic_train(e: int, f: any, fd: any, L: int, N: list, n: float, t: list) -> tuple[dict, dict]:
	b, w = ffnn_initalize(L, N)
	for _ in range(e):
		for x, yt in t:
			a, _, z = ffnn_forward_propagate(b, f, L, N, w, x)
			db, dw, = ffnn_backward_propagate(a, fd, L, N, yt, w, z)
			b, w = ffnn_gradient_descent(b, db, L, N, n, w, dw)
	return b, w

def ffnn_predict(b: dict, f: any, L: int, N: list, w: dict, x: list) -> None:
	_, y, _ = ffnn_forward_propagate(b, f, L, N, w, x)
	print(y)

if __name__ == "__main__":
	t = [
		([0, 0, 0], [0, 0]),
		([0, 0, 1], [0, 1]),
		([0, 1, 0], [0, 1]),
		([0, 1, 1], [1, 0]),
		([1, 0, 0], [0, 1]),
		([1, 0, 1], [1, 0]),
		([1, 1, 0], [1, 0]),
		([1, 1, 1], [1, 1])
	]


	'''print("TRAIN")


	fn = "TanH"
	f, fd = ffnn_functions(fn)
	L = 4
	N = [3, 8, 4, 2]
	b, w = ffnn_basic_train(512, f, fd, L, N, 0.15, t)
	for x, _ in t:
		ffnn_predict(b, f, L, N, w, x)


	print("SAVE/LOAD")


	ffnn_save(b, fn, L, N, w)'''
	b, fn, L, N, w = ffnn_load()
	f, fd = ffnn_functions(fn)
	for x, _ in t:
		ffnn_predict(b, f, L, N, w, x)

