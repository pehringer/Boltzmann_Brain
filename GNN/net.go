package main

import (
	"fmt"
	"math"
)

/*
A network can be encoded as a list of parameters and set of activations:

  Activations                      |  Parameters
  __[1]___[2]___[3]___[4]___[5]__  |  _____________
                                   |
  [ A.A , A.A , 0.0 , 0.0 , 0.0 ]  |                      Set first N activations to N inputs [ A.A, A.A].
                                   |
                                   |                       _____________
  [ A.A , A.A , B.B , 0.0 , 0.0 ]  |  ( W , 2 ,  0.9 )    2   0.9  | 0.5\__   A series of weights followed
                                   |  ( W , 1 , -2.7 )     ________|____/  3  by a bias describes a neuron.
                                   |  ( B , 3 ,  0.5 )    1  -2.7
                                   |
                                   |                                ____
  [ A.A , A.A , B.B , 0.0 , C.C ]  |  ( W , 3 ,  1.5 )     ________|-0.3\__   act  = f(act  * 1.5 + -0.3)
                                   |  ( B , 5 , -0.3 )    3   1.5  |____/  5     5        3
                                   |
                                   |                       _____________
  [ A.A , A.A , B.B , D.D , C.C ]  |  ( W , 1 ,  1.1 )    1   1.1  | 0.8\__   act  = f(act  * 1.1 + act  * -0.3 + 0.8)
                                   |  ( W , 2 , -0.3 )     ________|____/  4     4        1            2
                                   |  ( B , 4 ,  0.8 )    2  -0.3
                                   |
                                   |
                                   |  ( W , 4 , -2.1 )    Since there is no bias parameter the result
                                   |  ( W , 1 , -0.3 )    of these weight calculations are not stored.
                                   |
                                   |
  [ A.A , A.A , B.B , D.D , C.C ]  |                   Set N outputs from last N activations [ D.D, C.C].
                                  _|_
                                  \ /
                                   '
*/

type Param struct {
	Type	rune
	Index	int64
	Value	float64
}

type Net struct {
	activation	[]float64
	parameter	[]Param
}

func NewNetwork(activations, maxParameters int64) {
	return Net{
		make([]float64, activations),
		make([]Param, 0, maxParameters),
	}
}

func (n Network) Run(input []float64, outputs int64) []float64 {
	if len(n.activation) < len(input) {
		panic("too many inputs")
	}
	if len(n.activation) < outputs {
		panic("too many outputs")
	}
	for i, _ := range < n.activation {
		n.activation[i] = 0.0
	}
	for i, v := range input {
		n.activation[i] = i
	}
	summation := 0.0
	for _, p := n.parameter
		switch p.Type {
		case "W":
			summation += n.activation[p.Index] * p.Value
		case "B":
			summation += p.Value
			n.activation[p.Index] = math.Tanh(summation)
		}
	}
	return n.activation[len(n.activation)-outputs:]
}

func main() {
}
