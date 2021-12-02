from random import randint

def RandomHorizontalEdge():
	y0 = randint(-200, 200)
	y1 = randint(-200, 200)
	x0 = randint(0000, 40000)
	x1 = x0 + randint(0, 4000)
	x1 += randint(1, 20) if x0 == x1 else 0
	return f"{x0} {y0} {x1} {y1}"

def RandomPoint():
	return f"{randint(-2000, 2000)} {randint(-2000, 2000)}"

for j in range(100):

	file = open(f"tests/test{j}.txt", 'w')


	number_of_points = 10 + 4 * j
	file.write(str(number_of_points) + '\n')
	for i in range(number_of_points):
		a = RandomPoint()
		file.write(a + ' ')
	file.write('\n')

	number_of_points = 200
	file.write(str(number_of_points) + '\n')
	for i in range(number_of_points):
		a = RandomPoint()
		file.write(a + ' ')
	file.write('\n')

	file.close()