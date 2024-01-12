/*
A neural network parmater can be encoded as a ordered pair consisting of a
integer and decimal value.

               ( - 123 , +4.56 )                   ( + 789 , -0.12 )
                 ^  ^      ^                         ^  ^      ^
                /  /      /                         /  /      /
  Bias parameter  /      /          Weight parameter  /      /
        For neuron      /                  From neuron      /
              With value                          With value


A neural network neuron can be encoded as a series of parameters consisting
of a bias parameter followed by zero to many weight parameters.
                         _____                              _____
  (-5, -1.94)  1________/  5  \     (-3, -0.51)            /  3  \
  (+1, +0.73)    +0.73 /       \    (+5, +0.85)   5_______/       \
  (+2, -0.68)  2_______\ +1.94 /                    +0.85 \ -0.51 /
                 -0.68  \_____/                            \_____/

A neural network can be encode as a series of neurons and its activation
order is determined by the ordering of the neurons
                 _____                 _____                 _____
  (-5, +1.94)   /  1  \               /  5  \               /  3  \
  (+1, +0.73)  /       \_____________/       \_____________/       \
  (+2, -0.68)  \       /    +0.73   /\ +1.94 /\   +0.85    \ -0.51 /
  (-3, -0.51)   \_____/            /  \_____/  \            \_____/
  (+5, +0.85)              _______/             \_______
  (-4, +2.21)    _____    / -0.68                 -0.36 \    _____
  (+5, -0.36)   /  2  \  /                               \  /  4  \
  (+2, +1.49)  /       \/_________________________________\/       \
               \       /               +1.49               \ +2.21 /
                \_____/                                     \_____/
*/

type ParamPair struct {
	Meta	int64
	Param	float64
}

func (*p Pair) 




