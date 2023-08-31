from random import randrange, random, uniform


'''

Individual Network: (For Two Input Gates)

                  bias
                   |
                   |
(Input1)*-----*(Hidden1)*      bias
         \   /           \      |
          \ /             \     |
           *      bias     *(Output1)
          / \      |      /
         /   \     |     /
(Input2)*-----*(Hidden2)*



Individual Format:

 Hidden Weights                                          Hidden Biases                   Output Weights              Output Biases
 ======================================================  ==============================  ==========================  ==============
[<Hidden1_W1>, <Hidden1_W2>, <Hidden2_W1>, <Hidden2_W2>, <Hidden1_Bias>, <Hidden2_Bias>, <Output1_W1>, <Output1_W2>, <Output1_Bias>]

'''


def initialization(size: int) -> list[list[float]]:
	'''
	Create an initial population of potential solutions (individuals) using
	random or heuristic methods.
	'''
	if size % 2 != 0:
		raise ValueError("Size must evenly divisible by 2.")
	# Create population with random network values as small floats.
	population = []
	for i in range(size):
		individual = []
		for f in range(9):
			individual.append(random())
		population.append(individual)
	return population


def forward_prop(network: list[float], inputs: list[float]) -> float:
	hidden = [0.0, 0.0]
	# Calculate hidden neurons activations:
	#           ReLu(    bias +       (inputs * weights                               ) )
	#           -------- ------------ ------------------------------------------------- -
	hidden[0] = max(0.0, network[4] + (inputs[0] * network[0] + inputs[1] * network[1]) )
	hidden[1] = max(0.0, network[5] + (inputs[0] * network[2] + inputs[1] * network[3]) )
	# Calculate output neurons activations:
	#      ReLu(    bias +       (inputs * weights                               ) )
	#      -------- ------------ ------------------------------------------------- -
	return max(0.0, network[8] + (hidden[0] * network[6] + hidden[1] * network[7]) )


def fitness_func(individual: list[float], inputs: list[list[float]], outputs: list[float]) -> float:
	# Similar to batch learning, run all inputs to get the total error.
	error = 0.0
	for input, expected  in zip(inputs, outputs):
		output = forward_prop(individual, input)
		error += abs(output - expected)
	return error


def fitness_evaluation(population: list[list[float]], inputs: list[list[float]], outputs: list[float]) -> None:
	'''
	Evaluate the fitness of each individual in the population based on a
	defined fitness function, which measures how well they solve the
	problem at hand.
	'''
	# Sort the population from most to least fit (small error = fit).
	population.sort(key=lambda i: fitness_func(i, inputs, outputs))


def selection(population: list[list[float]]) -> list[list[float]]:
	'''
	Select individuals from the current population based on their fitness.
	Individuals with higher fitness values are more likely to be selected.
	'''
	# Select the first half of the population (most fit individuals).
	return population[:len(population) // 2]


def mutation(selected: list[list[float]], rate: float) -> list[list[float]]:
	'''
	Introduce small random changes in the genetic material of the selected
	individuals to generate new solutions (offspring).
	'''
	offspring = []
	for i in selected:
		# Create new mutated genetics for each offspring.
		genetics = []
		for val in i:
			# Randomly mutate offspring vals at the given rate.
			if random() <= rate:
				val += uniform(-0.2, 0.2)
			genetics.append(val)
		offspring.append(genetics)
	return offspring


def replacement(population: list[int], offspring: list[int]) -> None:
	'''
	Replace some individuals from the current population with the newly
	created offspring. This maintains the population size.
	'''
	# Replace second half of the population (least fit individuals).
	population[len(population) // 2:] = offspring


def termination(population: list[list[float]], inputs: list[list[float]], outputs: list[float], error: float) -> tuple[float, bool]:
	'''
	Check if a termination criterion is met, such as reaching a maximum
	number of generations or achieving a satisfactory solution.
	'''
	# Return population fitness is at or above a certain level.
	fitness = sum([fitness_func(i, inputs, outputs) for i in population]) / len(population)
	return fitness, fitness <= error


def mutation_only_genetic_algorithm(size: int, generations: int, inputs: list[list[float]], outputs: list[float], rate: float, error: float):
	gen = 0
	term = False
	# Step 1:
	population = initialization(size)
	while gen < generations and not term:
		# Step 2:
		fitness_evaluation(population, inputs, outputs)
		# Step 3:
		selected = selection(population)
		# Step 4:
		offspring = mutation(selected, rate)
		# Step 5:
		replacement(population, offspring)
		# Step 6:
		err, term = termination(population, inputs, outputs, error)
		print("Generation %d, Error: %f" % (gen, err))
		gen += 1
	for input, expected  in zip(inputs, outputs):
		output = forward_prop(population[1], input)
		print("%f %f = %f (%f)" % (input[0], input[1], output, expected))


inputs = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]]

OR = [0.0, 1.0, 1.0, 1.0]
NOR = [1.0, 0.0, 0.0, 0.0]
AND = [0.0, 0.0, 0.0, 1.0]
NAND = [1.0, 1.0, 1.0, 0.0]
mutation_only_genetic_algorithm(64, 1024, inputs, OR, 0.8, 0.35)

XOR = [0.0, 1.0, 1.0, 0.0]
mutation_only_genetic_algorithm(512, 1024, inputs, XOR, 0.8, 0.35)
