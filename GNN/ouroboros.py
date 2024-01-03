from random import randrange, random, uniform

def init_indiv(Ni: int, Nh: int, No: int) -> tuple[dict, dict]:
	b = {}
	for i in range(Ni, Ni+Nh+No):
		b[i] = uniform(-1.0, 1.0)
	w = {}
	for j in range(Ni, Ni+Nh+No):
		for i in range(0, Ni+Nh+No):
			w[(i,j)] = uniform(-1.0, 1.0)
	return b, w

if __name__ == "__main__":
	b, w = init_indiv(3, 8+4 , 2)
	print("BIASES")
	for i in b.items():
		print(i)
	print("WEIGHTS")
	for i in w.items():
		print(i)
