import random

file = open("test0.txt", "w")

for i in range(random.randint(0, 20000)):
	a = random.uniform(-100, 100)
	b = random.randint(0, 2**64-1)
	file.write(str(a) +" "+ str(b) +"\n")
	if (random.randint(0,10)==3):
		file.write( random.randint(0,10)*" " + "\n")

file.close()
