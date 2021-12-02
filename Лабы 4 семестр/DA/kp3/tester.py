from random import randint
import sys

def RandomPoint():
	return (randint(-2000, 2000), randint(-2000, 2000))

def RandomEdge():
	y = randint(-200, 200)
	x_1, x_2 = randint(-200, 200), randint(-200, 200)
	if x_1 > x_2:
		x_1, x_2 = x_2, x_1
	elif x_1 == x_2:
		x_2 += 1
	return (x_1, y, x_2, y)

edges = []

def NEOA(point):
	result = 0
	
	for edge in edges:
		if edge[0] <= point[0] <= edge[2] and point[1] < edge[1]:
			result += 1

	return result

try:
	number_of_tests = int(sys.argv[1])
except:
	number_of_tests = 100

for j in range(number_of_tests):

	edges.clear()

	file = open(f"tests/test{j}.txt", 'w')
	ans_file = open(f"tests/test{j}_ans.txt", 'w')

	number_of_edges = 3 + 2 * j

	file.write(str(number_of_edges*2) + '\n')
	for i in range(number_of_edges):
		a = RandomEdge()
		edges.append(a)
		file.write(f"{a[0]} {a[1]} {a[2]} {a[3]}\n")

	number_of_points = 200

	file.write(str(number_of_points) + '\n')
	for i in range(number_of_points):
		a = RandomPoint()

		number_edges_of_above = NEOA(a)

		file.write(f"{a[0]} {a[1]}\n")
		ans_file.write(f"{number_edges_of_above}\n")

	file.close()
	ans_file.close()