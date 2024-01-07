package main

import "fmt"
import "math/rand"

// Network
type Net struct {
	// Input Weights
	//                                TH           TH
	// iw   = iw[i][j] = weight from i   input to j   neuron.
	//   ij
	iw	[][]float32

	// Neuron Parameters
	//                                TH            TH
	// np   = np[i][j] = weight from i   neuron to j   neuron.
	//   ij
	//                            TH
	// np   = np[k][k] = bias of k   neuron.
	//   kk
	np	[][]float32
}

func RandomFloat() float32 {
	return rand.Float32() * 2.0 - 1.0
}

func NewNet(I, H, O int) (n Network) {
	n.I = [I]int
	n.H = [H]int
	n.O = [O]int
	v := 0
	for i := 0; i < I; i++ {
		n.I[i] = v
		v++
	}
	for i := 0; i < H; i++ {
		n.H[i] = v
		v++
	}
	for i := 0; i < O; i++ {
		n.O[i] = v
		v++
	}
	n.b = map[int]float32
	n.w = map[Pair]float32
	for j := range n.H {
		n.b[j] = RandFloat32()
		for i := range n.I {
			n.w[Pair{i, j}] = RandFloat32()
		}
		for i := range n.H {
			if i != j {
				n.w[Pair{i, j}] = RandFloat32()
			}
		}
	}
	for j := range n.O {
		n.b[j] = RandFloat32()
		for i := range n.H {
			n.w[Pair{i, j}] = RandFloat32()
		}
	}
	return n
}

func (n Network) Run(x []float32, c int) (y []float32) {
	a := map[int]float32
	for i := range n.H {
		a[i] = 0.0
	}
	for k := 0; k < c; k++ {
		for j := range n.H {
			a[j] = n.b[j]
			for i := range n.I {
				a[j] += a[i] * n.w[Pair{i, j}]
			}
			for i := range n.hidden {
				if i != j {
					a[j] += a[i] * n.w[Pair{i, j}]
				}
			}
		}
	}
}

func main() {
	fmt.Println("Hello Friend")
}
