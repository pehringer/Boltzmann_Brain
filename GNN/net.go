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

  (-5, -1.94)     +0.73   _____      (-3, -0.51)              _____
  (+1, +0.73)  1 ------->/  5  \     (+5, +0.85)     +0.85   /  3  \
  (+2, -0.68)           /       \                 5 ------->/       \
                  -0.68 \ +1.94 /                           \ -0.51 /
               2 ------->\_____/                             \_____/

A neural network can be encode as a series of neurons. The first neuron
activation calculated is the first in the series. The last neuron activation
calculated is the last in the series

  (-#, *#.##)
  (+#, *#.##)
  (+#, *#.##)
  (-#, *#.##)
  (+#, *#.##)
  (+#, *#.##)
  (-#, *#.##)
  (+#, *#.##)
*/
