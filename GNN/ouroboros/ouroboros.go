package main

import "fmt"
import "math"
import "math/rand"

type Network struct {
	bias	[]float64
	input	[][]float64
	weight	[][]float64
}

func RandomFloat() float64 {
	return rand.Float64() * 2.0 - 1.0
}

func NewNetwork(inputs, neurons int) Network {
	n := Network{
		make([]float64, neurons),
		make([][]float64, neurons),
		make([][]float64, neurons),
	}
	for i := 0; i < len(n.bias); i++ {
		n.bias[i] = RandomFloat()
	}
	for r := 0; r < len(n.input); r++ {
		n.input[r] = make([]float64, inputs)
		for c := 0; c < len(n.input[r]); c++ {
			n.input[r][c] = RandomFloat()
		}
	}
	for r := 0; r < len(n.weight); r++ {
		n.weight[r] = make([]float64, neurons)
		for c := 0; c < len(n.weight[r]); c++ {
			n.weight[r][c] = RandomFloat()
		}
	}
	return n
}

func (n Network) Overwrite(source Network) {
	for i := 0; i < len(n.bias); i++ {
		n.bias[i] = source.bias[i]
	}
	for r := 0; r < len(n.input); r++ {
		for c := 0; c < len(n.input[r]); c++ {
			n.input[r][c] = source.input[r][c]
		}
	}
	for r := 0; r < len(n.weight); r++ {
		for c := 0; c < len(n.weight[r]); c++ {
			n.weight[r][c] = source.weight[r][c]
		}
	}
}

func (n Network) MutateOne() {
	i := rand.Int() % 3
	if i == 0 {
		j := rand.Int() % len(n.bias)
		n.bias[j] += RandomFloat()
	} else if i == 1 {
		j := rand.Int() % len(n.input)
		k := rand.Int() % len(n.input[j])
		n.input[j][k] += RandomFloat()
	} else if i == 2 {
		j := rand.Int() % len(n.weight)
		k := rand.Int() % len(n.weight[j])
		n.weight[j][k] += RandomFloat()
	}
}

func (n Network) MutateMany() {
	j := rand.Int() % len(n.bias)
	if rand.Int() % 2 == 0 {
		n.bias[j] = RandomFloat()
		for i := 0; i < len(n.input[j]); i++ {
			n.input[j][i] = RandomFloat()
		}
		for i := 0; i < len(n.weight[j]); i++ {
			n.weight[j][i] = RandomFloat()
		}
	} else {
		n.bias[j] = 0.0
		for i := 0; i < len(n.input[j]); i++ {
			n.input[j][i] = 0.0
		}
		for i := 0; i < len(n.weight[j]); i++ {
			n.weight[j][i] = 0.0
		}
	}
}

func (n Network) Propagate(input, activation []float64) {
	for j := 0; j < len(n.bias); j++ {
		z := n.bias[j]
		for i, a := range input {
			z += a * n.input[j][i]
		}
		for i, a := range activation {
			z += a * n.weight[j][i]
		}
		//activation[j] = math.Tanh(z)
		activation[j] = math.Max(0.0, z)
	}
}

func (n Network) Fitness(input, output [][]float64) float64 {
	e := 0.0
	for i, x := range input {
		a := make([]float64, len(n.bias))
		n.Propagate(x, a)
		yt := output[i]
		y := a[len(a) - len(yt):]
		for j := 0; j < len(y); j++ {
			e += math.Abs(yt[j] - y[j])
		}
	}
	return e
}

func main() {
	input := [][]float64{
		{0.0, 0.0},
		{0.0, 1.0},
		{1.0, 0.0},
		{1.0, 1.0},
	}
	output := [][]float64{
		{0.0},
		{0.0},
		{0.0},
		{1.0},
	}
	parent := NewNetwork(2, 4)
	offspring := NewNetwork(2, 4)
	for i := 0; i < 4096; i++ {
		pf := parent.Fitness(input, output)
		of := offspring.Fitness(input, output)
		fmt.Printf("Error %d: %2.8f\n", i, pf)
		if of < pf {
			parent.Overwrite(offspring)
		}
		if i % 16 > 0 {
			offspring.MutateOne()
		} else {
			offspring.MutateMany()
		}
	}
        for i, x := range input {
	        a := make([]float64, len(parent.bias))
	        parent.Propagate(x, a)
	        yt := output[i]
	        y := a[len(a) - len(yt):]
	        for j := 0; j < len(y); j++ {
	                fmt.Printf("%2.8f %2.8f\n", yt[j], y[j])
	        }
		fmt.Println()
	}
}
