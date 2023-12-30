import random
import math

def initalize_parameter(L: int, N: list) -> tuple[dict, dict]:
	b = {}
	w = {}
	for l in range(1, L):
		for j in range(0, N[l]):
			b[(l,j)] = random.random()
			for i in range(0, N[l-1]):
				w[(l,i,j)] = random.random()
	return b, w

def forward_propagate(b: dict, f: any, L: int, N: list, w: dict, x: list) -> tuple[dict, list, dict]:
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

def backward_propagate(a: dict, fd: any, L: int, N: list, yt: list, w: dict, z: dict) -> tuple[dict, dict]:
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

def gradient_descent(b: dict, db: dict, L: int, N: list, n: float, w: dict, dw: dict) -> tuple[dict, dict]:
	for l in range(1, L):
		for j in range(0, N[l]):
			b[(l,j)] = b[(l,j)] - n * db[(l,j)]
			for i in range(0, N[l-1]):
				w[(l,i,j)] = w[(l,i,j)] - n * dw[(l,i,j)]
	return b, w

def stochastic_gradient_descent(e: int, f: any, fd: any, L: int, N: list, n: float, t: list) -> tuple[dict, dict]:
	b, w = initalize_parameter(L, N)
	for _ in range(e):
		for x, yt in t:
			a, _, z = forward_propagate(b, f, L, N, w, x)
			db, dw, = backward_propagate(a, fd, L, N, yt, w, z)
			b, w = gradient_descent(b, db, L, N, n, w, dw)
	return b, w

def print_prediction(b: dict, f: any, L: int, N: list, w: dict, x: list) -> None:
	_, y, _ = forward_propagate(b, f, L, N, w, x)
	print(y)

def tanh(z: float) -> float:
	return math.tanh(z)

def tanh_d(z: float) -> float:
	return 1 - tanh(z) ** 2

if __name__ == "__main__":
	f = tanh
	fd = tanh_d
	L = 4
	N = [3, 8, 4, 2]
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

	b, w = stochastic_gradient_descent(512, tanh, tanh_d, L, N, 0.15, t)

	for x, _ in t:
		print_prediction(b, f, L, N, w, x)
