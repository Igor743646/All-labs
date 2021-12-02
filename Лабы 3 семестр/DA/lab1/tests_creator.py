import random
import string

def main():
	
	for i in range(3):
		file_name = "test"+str(i)+".txt"
		file = open(file_name, "w")
		for j in range(1000*(10**i)):
			slovo = ""
			for k in range(random.randint(1, 64)):
				slovo+=random.choice(string.ascii_letters)
			file.write(str(random.randint(0, 2**16-1)) + " " + slovo + "\n")
		file.close()

main()