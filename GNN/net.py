import random

POPULATION_SIZE = 4096 * 8

NUMBER_GENERATIONS = 4096

MAX_GENOME_SIZE = 16

TRAINING_PAIRS = [
	([0.0, 0.0], [0.0, 0.0]),
	([0.0, 1.0], [1.0, 0.0]),
	([1.0, 0.0], [1.0, 0.0]),
	([1.0, 1.0], [0.0, 0.0]),
]

# Create population.
population = []
for _ in range(POPULATION_SIZE):
	fitness = 0.0
	genome = []
	individual = (fitness, genome)
	population.append(individual)

# Simulate generations.
for generation in range(NUMBER_GENERATIONS):
	# Mutate individuals in population.
	for individual in population[len(population)//8:]:
		_, genome = individual
		while random.random() < 0.8:
			possible_lower = 0 if len(genome) < MAX_GENOME_SIZE else 2
			possible_upper = 5 if len(genome) > 0 else 1
			match random.randrange(possible_lower, possible_upper):
				# Insert gene.
				case 0:
					position = random.randrange(0, len(genome)+1)
					metadata = random.randrange(-MAX_GENOME_SIZE+1, MAX_GENOME_SIZE)
					data = random.random()
					gene = (metadata, data)
					genome.insert(position, gene)
				# Copy genes.
				case 1:
					start = random.randrange(0, len(genome)+1)
					end = random.randrange(start, len(genome)+1)
					position = random.randrange(0, len(genome)+1)
					while start < end:
						genome.insert(position, genome[start])
						start += 1
						position += 1
				# Remove gene.
				case 3:
					position = random.randrange(0, len(genome))
					genome.pop(position)
				# Change gene integer.
				case 4:
					position = random.randrange(0, len(genome))
					metadata = random.randrange(-MAX_GENOME_SIZE+1, MAX_GENOME_SIZE)
					_, data = genome[position]
					gene = (metadata, data)
					genome[position] = gene
				# Change gene decimal.
				case 5:
					position = random.randrange(0, len(genome))
					metadata, data = genome[position]
					data += random.uniform(-0.1, 0.1)
					gene = (metadata, data)
					genome[position] = gene
	# Evaluate individuals fitness in population.
	for individual in range(len(population)):
		fitness = 0.0
		_, genome = population[individual]
		for pair in TRAINING_PAIRS:
			# Run genome (network) with input.
			input, expected_output = pair
			activation = [0.0] * MAX_GENOME_SIZE
			for i in range(len(input)):
				activation[i] = input[i]
			summation = 0.0
			for gene in genome:
				metadata, data = gene
				# Weight parameter.
				if metadata >= 0:
					summation += activation[metadata] * data
				# Bias parameter.
				elif metadata < 0:
					summation += data
					activation[-metadata] = max(0.0, summation)
					summation = 0.0
			# Get genome (network) error of output.
			output = activation[-len(expected_output):]
			for i in range(len(expected_output)):
				fitness += abs(expected_output[i] - output[i])
		population[individual] = (fitness, genome)
	# Select individuals and duplicate.
	population.sort()
	select = len(population) // 2
	for individual in range(select):
		fitness, genome = population[individual]
		duplicate = [gene for gene in genome]
		population[individual+select] = (fitness, duplicate)
	# Print best fitness
	print("Generation:", generation)
	print(population[0][0])


fitness, genome = population[0]
for pair in TRAINING_PAIRS:
	# Run genome (network) with input.
	input, expected_output = pair
	activation = [0.0] * MAX_GENOME_SIZE
	for i in range(len(input)):
		activation[i] = input[i]
	summation = 0.0
	for gene in genome:
		metadata, data = gene
		# Weight parameter.
		if metadata >= 0:
			summation += activation[metadata] * data
		# Bias parameter.
		elif metadata < 0:
			summation += data
			activation[-metadata] = max(0.0, summation)
			summation = 0.0
	# Get genome (network) error of output.
	output = activation[-len(expected_output):]
	print(input, expected_output, output)







