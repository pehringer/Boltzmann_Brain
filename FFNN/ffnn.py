import random
import math
import time




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
			b[(l,j)] = random.uniform(-1.0, 1.0)
			for i in range(0, N[l-1]):
				w[(l,i,j)] = random.uniform(-1.0, 1.0)
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




def print_training_network() -> int:
        print("Training Network")
        return 1, 0.0
def print_epoch_error(i: int, ee: float) -> int:
        print("\u001b[1F\u001b[2KEpoch:", str(i), "Error:", str(ee))
        return i + 1, 0.0
def print_network_trained() -> None:
        print("\u001b[1F\u001b[2KNetwork Trained")
def ffnn_train(e: int, f: any, fd: any, L: int, N: list, n: float, t: list) -> tuple[dict, dict]:
	b, w = ffnn_initalize(L, N)
	i, ee = print_training_network()
	for _ in range(e):
		for x, yt in t:
			a, _, z = ffnn_forward_propagate(b, f, L, N, w, x)
			db, dw, = ffnn_backward_propagate(a, fd, L, N, yt, w, z)
			b, w = ffnn_gradient_descent(b, db, L, N, n, w, dw)
			ee += sum([abs(yt[i] - a[(L-1,i)]) for i in range(N[L-1])])
		i, ee = print_epoch_error(i, ee)
	print_network_trained()
	return b, w




def print_saving_network() -> int:
	print("Saving Network")
	return 1
def print_parameters_saved(i: int) -> int:
	print("\u001b[1F\u001b[2KParameters Saved:", str(i))
	return i + 1
def print_network_saved() -> None:
	print("\u001b[1F\u001b[2KNetwork Saved")
def ffnn_save(b: dict, fn: str, L: int, N: list, w: dict):
	i = print_saving_network()
	f = open("parameters.txt", "w")
	f.write("fn" + " " + fn + "\n")
	f.write("L" + " " + str(L) + "\n")
	for n in N:
		f.write("N" + " " + str(n) + "\n")
	for k, v in b.items():
		l, i = k
		f.write("b" + " " + str(l) + " " + str(i) + " " + str(v) + "\n")
		i = print_parameters_saved(i)
	for k, v in w.items():
		l, i, j = k
		f.write("w" + " " + str(l) + " " + str(i) + " " + str(j) + " " + str(v) + "\n")
		i = print_parameters_saved(i)
	f.close()
	print_network_saved()




def print_loading_network() -> int:
	print("Loading Network")
	return 1
def print_parameters_loaded(i: int) -> int:
	print("\u001b[1F\u001b[2KParameters Loaded:", str(i))
	return i + 1
def print_network_loaded() -> None:
	print("\u001b[1F\u001b[2KNetwork Loaded")
def ffnn_load() -> tuple[dict, str, int, list, dict]:
	b = {}
	fn = ""
	L = 0
	N = []
	w = {}
	f = open("ffnn.txt", "r")
	i = print_loading_network()
	for l in f.readlines():
		t = l.split()
		match t[0]:
			case "b":
				i = print_parameters_loaded(i)
				b[(int(t[1]), int(t[2]))] = float(t[3])
			case "fn":
				fn = str(t[1])
			case "L":
				L = int(t[1])
			case "N":
				N += [int(t[1])]
			case "w":
				i = print_parameters_loaded(i)
				w[(int(t[1]), int(t[2]), int(t[3]))] = float(t[4])
	f.close()
	print_network_loaded()
	return b, fn, L, N, w




def mnist_load(filepath: str) -> list[tuple]:
	t = []
	f = open(filepath, "r")
	for l in f.readlines()[1:]:
		l = l.split(",")
		yt = ([0.0] * 10)
		yt[int(l[0])] = 1.0
		x = [float(v) for v in l[1:]]
		t.append((x, yt))
	f.close()
	return t


if __name__ == "__main__":
	t = mnist_load("mnist_test.csv")[:100]
	fn = "TanH"
	f, fd = ffnn_functions(fn)
	L = 4
	N = [len(t[0][0]), 16, 16, len(t[0][1])]
	b, w = ffnn_train(128, f, fd, L, N, 0.05, t)
	ffnn_save(b, fn, L, N, w)

