from random import randrange, random


def initialization(size: int) -> list[str]:
	'''
	Create an initial population of potential solutions (individuals) using
        random or heuristic methods.
	'''
	if size % 2 != 0:
		raise ValueError("Size must evenly divisible by 2.")
	# Create population with random RGB values as binary strings.
	population = []
	for i in range(size):
		# Generate random colors.
		red = format(randrange(0, 256), "08b")
		green = format(randrange(0, 256), "08b")
		blue = format(randrange(0, 256), "08b")
		population.append(red + green + blue)
	return population


def fitness_func(individual: str, red: int, green: int, blue: int) -> float:
	# Extract individuals colors.
	genetics_red = int(individual[0:8], 2)
	genetics_green = int(individual[8:16], 2)
	genetics_blue = int(individual[16:24], 2)
	# Calculate color differance.
	differance = abs(genetics_red - red)
	differance += abs(genetics_green - green)
	differance += abs(genetics_blue - blue)
	# Calculate fitness score
	return 1 - differance / 765


def fitness_evaluation(population: list[str], red: int, green: int, blue: int) -> None:
	'''
	Evaluate the fitness of each individual in the population based on a
	defined fitness function, which measures how well they solve the
	problem at hand.
	'''
	# Sort the population from most to least fit.
	population.sort(key=lambda i: fitness_func(i, red, green, blue), reverse=True)



def selection(population: list[str]) -> list[str]:
	'''
	Select individuals from the current population based on their fitness.
	Individuals with higher fitness values are more likely to be selected.
	'''
	# Select the first half of the population (most fit individuals).
	return population[:len(population) // 2]


def crossover(parents: list[str]) -> list[str]:
	'''
	Create new individuals (offspring) by combining genetic information
	from selected parents. Crossover points are chosen in the genetic
	material to exchange information.
	'''
	# Create equal number of offspring from parents.
	offspring = []
	for p in range(len(parents)):
		# Randomly select parents.
		male = parents[randrange(0, len(parents))]
		female = parents[randrange(0, len(parents))]
		# Randomly crossover.
		point = randrange(1,24)
		genetics = male[:point] + female[point:]
		offspring.append(genetics)
	return offspring


def mutation(offspring: list[str], rate: float) -> None:
	'''
	Introduce small random changes in the genetic material of the offspring
	to add diversity to the population.
	'''
	for i in range(len(offspring)):
		# Create new mutated genetics for each offspring.
		genetics = ""
		for bit in offspring[i]:
			# Randomly flip offspring bits at the given rate.
			if random() <= rate:
				bit = '1' if bit == '0' else '0'
			genetics += bit
		offspring[i] = genetics


def replacement(population: list[str], offspring: list[str]) -> None:
	'''
	Replace some individuals from the current population with the newly
	created offspring. This maintains the population size.
	'''
	# Replace second half of the population (least fit individuals).
	population[len(population) // 2:] = offspring


def termination(population: list[str], red: int, green: int, blue: int, level: float) -> tuple[float, bool]:
	'''
	Check if a termination criterion is met, such as reaching a maximum
	number of generations or achieving a satisfactory solution.
	'''
	# Return population fitness is at or above a certain level.
	fitness = sum([fitness_func(i, red, green, blue) for i in population]) / len(population)
	return fitness, fitness >= level


def print_population(population: list[str]):
	for i in  population:
		red = int(i[0:8], 2)
		green = int(i[8:16], 2)
		blue = int(i[16:24], 2)
		print("\033[38;2;%d;%d;%dm %s \033[0m" % (red, green, blue, i), end="")
	print()


def mutation_only_genetic_algorithm(size: int, generations: int, rate: float, red: int, green: int, blue: int, level: float):
	gen = 0
	term = False
	# Step 1:
	population = initialization(size)
	while gen < generations and not term:
		# Step 2:
		fitness_evaluation(population, red, green, blue)
		# Step 3:
		selected = selection(population)
		# Step 4:
		offspring = crossover(selected)
		# Step 5:
		mutation(offspring, rate)
		# Step 6:
		replacement(population, offspring)
		# Step 7:
		fit, term = termination(population, red, green, blue, level)
		print("Generation %d, Fitness: %f" % (gen, fit))
		print_population(population)
		gen += 1


mutation_only_genetic_algorithm(16, 64, 0.01, 255, 255, 0, 0.90)
