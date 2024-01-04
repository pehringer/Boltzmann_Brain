from random import randrange, random, uniform

def init_indiv(Ni: int, Nh: int, No: int) -> tuple[float, dict, dict]:
	b = {i: uniform(-1.0, 1.0) for i in range(Ni, Ni+Nh+No)}
	w = {}
	for j in range(Ni, Ni+Nh+No):
		for i in range(0, Ni+Nh+No):
			if j != i:
				w[(i,j)] = uniform(-1.0, 1.0)
	w = {(i, j): uniform(-1.0, 1.0) for}
	return 0.0, b, w

def init_pop(P, Ni, Nh, No) -> list[tuple]:
	return [init_indiv(Ni,Nh,No) for i in range(P)]

if __name__ == "__main__":
	b, w = init_indiv(2, 2, 2)
	print("BIASES")
	for i in b.items():
		print(i)
	print("WEIGHTS")
	for i in w.items():
		print(i)
