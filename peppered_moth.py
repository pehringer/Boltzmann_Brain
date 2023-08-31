from random import randrange, random


def initialization(size: int) -> list[int]:
	'''
	Create an initial population of potential solutions (individuals) using
        random or heuristic methods.
	'''
	if size % 2 != 0:
		raise ValueError("Size must evenly divisible by 2.")
	# Create population with random greyscale values as integers.
	return [randrange(240, 256) for i in range(size)]


def fitness_func(individual: int, target: int) -> float:
	return 1 - abs(individual - target) / 255


def fitness_evaluation(population: list[int], target: int) -> None:
	'''
	Evaluate the fitness of each individual in the population based on a
	defined fitness function, which measures how well they solve the
	problem at hand.
	'''
	# Sort the population from most to least fit.
	population.sort(key=lambda i: fitness_func(i, target), reverse=True)


def selection(population: list[int]) -> list[int]:
	'''
	Select individuals from the current population based on their fitness.
	Individuals with higher fitness values are more likely to be selected.
	'''
	# Select the first half of the population (most fit individuals).
	return population[:len(population) // 2]


def mutation(selected: list[str]) -> list[int]:
	'''
	Introduce small random changes in the genetic material of the selected
        individuals to generate new solutions (offspring).
	'''
	# Create mutate offspring from selected individuals at given rate.
	return [randrange(max(0, i-8), min(256, i+9)) for i in selected]


def replacement(population: list[int], offspring: list[int]) -> None:
	'''
	Replace some individuals from the current population with the newly
	created offspring. This maintains the population size.
	'''
	# Replace second half of the population (least fit individuals).
	population[len(population) // 2:] = offspring


def termination(population: list[int], target: int, level: float) -> tuple[float, bool]:
	'''
	Check if a termination criterion is met, such as reaching a maximum
	number of generations or achieving a satisfactory solution.
	'''
	# Return population fitness is at or above a certain level.
	fitness = sum([fitness_func(i, target) for i in population]) / len(population)
	return fitness, fitness >= level


def print_population(population: list[int]):
        for i in  population:
                print("\033[38;2;%d;%d;%dm %s \033[0m" % (i, i, i, i), end="")
        print()


def mutation_only_genetic_algorithm(size: int, generations: int, target: int, level: float):
	gen = 0
	term = False
	# Step 1:
	population = initialization(size)
	while gen < generations and not term:
		# Step 2:
		fitness_evaluation(population, target)
		# Step 3:
		selected = selection(population)
		# Step 4:
		offspring = mutation(selected)
		# Step 5:
		replacement(population, offspring)
		# Step 6:
		fit, term = termination(population, target, level)
		print("Generation %d, Fitness: %f" % (gen, fit))
		print_population(population)
		gen += 1


mutation_only_genetic_algorithm(16, 64, 15, 0.90)


