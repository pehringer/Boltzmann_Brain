package main

import "fmt"
import "math/rand"

type GeneNode {
	// meta < 0 = bias parameter.
	// meta > 0 = weight parameter.
	// |meta| = neuron number.
	metadata	int64
	parameter	float64
	next		*GeneNode
}

type GenomeList {
	length	int64
	head	*GeneNode
}


func RandomFloat() float64 {
	return rand.Float64() * 2.0 - 1.0
}

func main() {
	fmt.Println("Hello, friend.")
}
