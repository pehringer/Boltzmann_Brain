'''
  INPUT    OUTPUT
0 [w, w] 0 [b]
1 [w, w] 1 [w, b]
2 [w, w] 2 [w, w, b]
   0  1     0  1  2
  [x, x]   [y, y, y]
'''
import random

def net_new(X: int, Y: int) -> tuple[list, list]:
	XP = [[random.uniform(-0.1, 0.1) for c in range(X)] for r in range(Y)]
	YP = [[random.uniform(-0.1, 0.1) for c in range(r+1)] for r in range(Y)]
	return XP, YP

def net_run(X: list, XP: list, XPM: dict, YP: list, YPM: dict) -> list:
	Y = [0.0 for i in range(len(YP))]
	for i in range(len(YP)):
		y = 0.0
		for j in range(len(XP[i])):
			if (i,j) in XPM:
				y += X[j] * XPM[(i,j)]
			else:
				y += X[j] * XP[i][j]
		for j in range(len(YP[i])-1):
			if (i,j) in YPM:
				y += Y[j] * YPM[(i,j)]
			else:
				y += Y[j] * YP[i][j]
		if (i,-1) in YPM:
			y += YPM[(i,-1)]
		else:
			y += YP[i][-1]
		Y[i] = max(0.0, y)
	return Y

def net_err(T: list, XP: list, XPM: dict, YP: list, YPM: dict) -> float:
	e = 0.0
	for X, YT in T:
		Y = net_run(X, XP, XPM, YP, YPM)
		for y, yt in zip(Y[-len(YT):], YT):
			e += abs(y - yt)
	return e

def gnn_feature(XP: list, YP: list) -> tuple[dict, dict]:
	XPM = {}
	YPM = {}

	i = random.randrange(0, len(YP))
	j = random.randrange(0, len(XP[i]))
	XPM[(i,j)] = XP[i][j]
	if i > 0:
		j = random.randrange(0, len(YP[i])-1)
		YPM[(i,j)] = YP[i][j]
	YPM[(i,-1)] = YP[i][-1]

	i = random.randrange(0, len(YP))
	j = random.randrange(0, len(XP[i]))
	XPM[(i,j)] = XP[i][j]
	if i > 0:
		j = random.randrange(0, len(YP[i])-1)
		YPM[(i,j)] = YP[i][j]
	YPM[(i,-1)] = YP[i][-1]

	return XPM, YPM

def gnn_mutation(XPM: dict, YPM: dict) -> tuple[dict, dict]:
	XPMM = {}
	YPMM = {}
	for ij in XPM:
		XPMM[ij] = XPM[ij] + random.uniform(-0.1, 0.1)
	for ij in YPM:
		YPMM[ij] = YPM[ij] + random.uniform(-0.1, 0.1)
	return XPMM, YPMM

def gnn_combine(XP: list, XPM: list, YP: list, YPM: list) -> tuple[list, list]:
	for i, j in XPM:
		XP[i][j] = XPM[(i,j)]
	for i, j in YPM:
		YP[i][j] = YPM[(i,j)]
	return XP, YP

def net_train(T: list, XP: list, YP: list) -> tuple[float, list, list]:
	XPM, YPM = gnn_feature(XP, YP)
	e = net_err(T, XP, XPM, YP, YPM)
	for i in range(16):
		XPMM, YPMM = gnn_mutation(XPM, YPM)
		ee = net_err(T, XP, XPMM, YP, YPMM)
		if ee <= e:
			e = ee
			XPM = XPMM
			YPM = YPMM
	XP, YP = gnn_combine(XP, XPM, YP, YPM)
	return e, XP, YP

T_NOT = [
([0.0], [1.0]),
([1.0], [0.0]),
]

T_NOR = [
([0.0, 0.0], [1.0]),
([0.0, 1.0], [0.0]),
([1.0, 0.0], [0.0]),
([1.0, 1.0], [0.0]),
]

T_XOR = [
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

t_2bit_full_adder = [
([0.0, 0.0, 0.0, 0.0, 0.0], [0.0, 0.0, 0.0]),
([0.0, 0.0, 0.0, 1.0, 0.0], [1.0, 0.0, 0.0]),
([0.0, 0.0, 1.0, 0.0, 0.0], [1.0, 0.0, 0.0]),
([0.0, 0.0, 1.0, 1.0, 0.0], [0.0, 1.0, 0.0]),
([0.0, 1.0, 0.0, 0.0, 0.0], [1.0, 0.0, 0.0]),
([0.0, 1.0, 0.0, 1.0, 0.0], [0.0, 1.0, 0.0]),
([0.0, 1.0, 1.0, 0.0, 0.0], [0.0, 1.0, 0.0]),
([0.0, 1.0, 1.0, 1.0, 0.0], [1.0, 0.0, 1.0]),
([1.0, 0.0, 0.0, 0.0, 0.0], [1.0, 0.0, 0.0]),
([1.0, 0.0, 0.0, 1.0, 0.0], [0.0, 1.0, 0.0]),
([1.0, 0.0, 1.0, 0.0, 0.0], [0.0, 1.0, 0.0]),
([1.0, 0.0, 1.0, 1.0, 0.0], [1.0, 0.0, 1.0]),
([1.0, 1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0]),
([1.0, 1.0, 0.0, 1.0, 0.0], [1.0, 0.0, 1.0]),
([1.0, 1.0, 1.0, 0.0, 0.0], [1.0, 0.0, 1.0]),
([1.0, 1.0, 1.0, 1.0, 0.0], [0.0, 1.0, 1.0]),
([0.0, 0.0, 0.0, 0.0, 1.0], [0.0, 1.0, 0.0]),
([0.0, 0.0, 0.0, 1.0, 1.0], [1.0, 0.0, 1.0]),
([0.0, 0.0, 1.0, 0.0, 1.0], [1.0, 0.0, 1.0]),
([0.0, 0.0, 1.0, 1.0, 1.0], [0.0, 1.0, 1.0]),
([0.0, 1.0, 0.0, 0.0, 1.0], [1.0, 0.0, 1.0]),
([0.0, 1.0, 0.0, 1.0, 1.0], [0.0, 1.0, 1.0]),
([0.0, 1.0, 1.0, 0.0, 1.0], [0.0, 1.0, 1.0]),
([0.0, 1.0, 1.0, 1.0, 1.0], [1.0, 0.0, 1.0]),
([1.0, 0.0, 0.0, 0.0, 1.0], [1.0, 0.0, 1.0]),
([1.0, 0.0, 0.0, 1.0, 1.0], [0.0, 1.0, 1.0]),
([1.0, 0.0, 1.0, 0.0, 1.0], [0.0, 1.0, 1.0]),
([1.0, 0.0, 1.0, 1.0, 1.0], [1.0, 0.0, 1.0]),
([1.0, 1.0, 0.0, 0.0, 1.0], [0.0, 1.0, 1.0]),
([1.0, 1.0, 0.0, 1.0, 1.0], [1.0, 0.0, 1.0]),
([1.0, 1.0, 1.0, 0.0, 1.0], [1.0, 0.0, 1.0]),
([1.0, 1.0, 1.0, 1.0, 1.0], [0.0, 1.0, 1.0]),
]

T = t_2bit_full_adder
XP, YP = net_new(len(T[0][0]), 16)

for i in range(4096 * 16):
	e, XP, YP = net_train(T, XP, YP)
	print(i, e)
	if e < 0.7:
		break
	if i % 16 == 0 and e > 24.0:
		XPM, YPM = gnn_feature(XP, YP)
		XPM, YPM = gnn_mutation(XPM, YPM)
		XP, YP = gnn_combine(XP, XPM, YP, YPM)
	elif i % 32 == 0 and e > 12.0:
		XPM, YPM = gnn_feature(XP, YP)
		XPM, YPM = gnn_mutation(XPM, YPM)
		XP, YP = gnn_combine(XP, XPM, YP, YPM)
	elif i % 64 == 0 and e > 6.0:
		XPM, YPM = gnn_feature(XP, YP)
		XPM, YPM = gnn_mutation(XPM, YPM)
		XP, YP = gnn_combine(XP, XPM, YP, YPM)
	elif i % 128 == 0 and e > 3.0:
		XPM, YPM = gnn_feature(XP, YP)
		XPM, YPM = gnn_mutation(XPM, YPM)
		XP, YP = gnn_combine(XP, XPM, YP, YPM)
	elif i % 256 == 0 and e > 1.5:
		XPM, YPM = gnn_feature(XP, YP)
		XPM, YPM = gnn_mutation(XPM, YPM)
		XP, YP = gnn_combine(XP, XPM, YP, YPM)
for X, YT in T:
	Y = net_run(X, XP, {}, YP, {})
	print(X, YT, Y[-len(YT):])





