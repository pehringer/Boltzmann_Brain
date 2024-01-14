package main

import (
	"fmt"
)

/*
A parmater can be encoded as a pair of values:

             ( - # , #.# )
               | |    |
  Bias parameter |    |
    For activation    |
             With value

               ( + # , #.# )
                 | |    |
  Weight parameter |    |
     From activation    |
               With value



A network can be encoded as a list of parameters:

  Activations                      |  Parameters
  __[1]___[2]___[3]___[4]___[5]__  |  _____________
                                   |
  [ 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ]  |                   Set first N activations to N inputs [ A.A, A.A].
                                   |
                                   |                    _____________
  [ A.A , A.A , 0.0 , 0.0 , 0.0 ]  |  (  2 ,  0.9 )    2   0.9  | 0.5\__   A series of weights followed
                                   |  (  1 , -2.7 )     ________|____/  3  by a bias describes a neuron.
                                   |  ( -3 ,  0.5 )    1  -2.7
                                   |
                                   |                             ____
  [ A.A , A.A , B.B , 0.0 , 0.0 ]  |  (  3 ,  1.5 )     ________|-0.3\__   A series of weights followed
                                   |  ( -5 , -0.3 )    3   1.5  |____/  5  by a bias describes a neuron.
                                   |
                                   |                    _____________
  [ A.A , A.A , B.B , 0.0 , C.C ]  |  (  1 ,  1.1 )    1   1.1  | 0.8\__   A series of weights followed
                                   |  (  2 , -0.3 )     ________|____/  4  by a bias describes a neuron.
                                   |  ( -4 ,  0.8 )    2  -0.3
                                   |
                                   |
                                   |  (  4 , -2.1 )    Since there is no bias parameter the result
                                   |  (  1 , -0.3 )    of these weight calculations are not stored.
                                   |
                                   |
  [ A.A , A.A , B.B , D.D , C.C ]  |                   Set N outputs from last N activations [ D.D, C.C].
                                  _|_
                                  \ /
                                   '
*/

type ParameterPair struct {
	metadata	int64
	data		float64
}

func BiasPair(neuron int64, value float64) ParameterPair {
	if neuron <= 0 {
		panic("neuron cannot be less than 1")
	}
	return ParameterPair{-neuron, value}
}

func WeightPair(neuron int64, value float64) ParameterPair {
	if neuron <= 0 {
		panic("neuron cannot be less than 1")
	}
	return ParameterPair{neuron, value}
}

func (p ParameterPair)IsBias() bool {
	return p.metadata < 0
}

func (p ParameterPair) IsWeight() bool {
	return p.metadata > 0
}

func (p ParameterPair) GetNeuron() int64 {
	if p.metadata < 0 {
		return -p.metadata
	}
	return p.metadata
}

func (p ParameterPair) GetValue() float64 {
	return p.data
}

type NetworkList struct {
	activation	[]float64
	input		[]float64
	output		[]float64
	parameter	[]ParameterPair
}

func main() {
	ppl := []ParameterPair{
		BiasPair(3, 1.25),
		WeightPair(1, 1.5),
		WeightPair(2, -0.75),
		BiasPair(4, -0.25),
		WeightPair(3, 0.5),
	}
	for _, pp := range ppl {
		if pp.IsBias() {
			fmt.Println(pp.GetNeuron(), ":", pp.GetValue())
		} else if pp.IsWeight() {
			fmt.Println("\t", pp.GetNeuron(), "->", pp.GetValue())
		}
	}
}
