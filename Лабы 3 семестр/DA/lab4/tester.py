import random
import copy
from random import choice
from string import ascii_letters

randletter = lambda x=16: ''.join(choice(ascii_letters) for i in range(random.randint(0, x)))

def randstring():
	res = ""
	for _ in range(random.randint(1, 50)):
		res += randletter() + " "

	return res

if __name__ == "__main__":

	for i in range(150, 180):

		file = open("tests/test"+str(i)+".txt", "w")

		pattern = ""
		for _ in range(random.randint(1, 2)):
			pattern += choice([7,12,24,4])*(randletter() + " ")

		file.write(pattern + "\n")

		for _ in range((i+1)*100):
			file.write(choice([0,0,0,0,0,0,0,0,1])*randstring() + choice([1,1]) * pattern)


		file.close()