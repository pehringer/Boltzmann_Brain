package main

import "fmt"
import "math/rand"

type Pair struct {
	i	int;
	j	int;
}

type Network struct {
	input	[]int
	hidden	[]int
	output	[]int
	bias	map[int]float32
	weight	map[Pair]float32
}

func Rand_float32() float32 {
	return rand.Float32() * 2.0 - 1.0
}

func New_Network(input_count, hidden_count, output_count int) Network {
	n := Network{
		make([]int, input_count),
		make([]int, hidden_count),
		make([]int, output_count),
		make(map[int]float32),
		make(map[Pair]float32),
	}
	vertex_count := 0
	for i := 0; i < input_count; i++ {
		n.input[i] = vertex_count
		vertex_count++
	}
	for i := 0; i < hidden_count; i++ {
		n.hidden[i] = vertex_count
		vertex_count++
	}
	for i := 0; i < input_count; i++ {
		n.output[i] = vertex_count
		vertex_count++
	}
	for j := range n.hidden {
		n.bias[j] = Rand_float32()
		for i := range n.input {
			n.weight[Pair{i, j}] = Rand_float32()
		}
		for i := range n.hidden {
			if i != j {
				n.weight[Pair{i, j}] = Rand_float32()
			}
		}
	}
	for j := range n.output {
		n.bias[j] = Rand_float32()
		for i := range n.hidden {
			n.weight[Pair{i, j}] = Rand_float32()
		}
	}
	return n
}

func main() {
	fmt.Println("Hello Friend")
}
