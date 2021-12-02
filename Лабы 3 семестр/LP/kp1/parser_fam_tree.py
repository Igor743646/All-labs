import re

ged_file = open('family_tree.txt', 'r')

blocks = ["",]

i = 0
for string in ged_file:
	if string[0] == '0' and string[2] == '@':
		blocks.append("")
		i+=1
	blocks[i]+=string

person_id = {}
person_sex = {}
relationship = []

i=0
for block in blocks:
	if block[3] == 'I':
		ident = re.findall(r'0\s@I(\w+)@\sINDI', block)[0]
		sex = re.findall(r'1\sSEX\s.', block)[0][-1]
		name = re.findall(r'1\sNAME\s(\w+)', block)
		fname = re.findall(r'1\sNAME\s\w+\s/(\w+)/', block)[0] if re.findall(r'1\sNAME\s\w+\s/(\w+)/', block)!=[] else ""
		if name==[]: 
			name=['Undefind' + str(i)]
			i+=1
		
		person_id[ident]=name[0]+"_"+fname if fname!='' else name[0]
		person_sex[ident]= "male" if sex=='M' else "female"

	if block[3] == 'F':
		wife = re.findall(r'WIFE\s@I(\w+)', block)[0] if re.findall(r'WIFE\s@I(\w+)', block)!=[] else ""
		husband = re.findall(r'HUSB\s@I(\w+)', block) 
		children = re.findall(r'CHIL\s@I(\w+)', block)
		if husband==[]:
			husband = ["Undefind" + str(i)]
			i+=1

		for child in children: 
			try:
				relationship.append([person_id[wife], person_id[husband[0]], person_id[child]])
			except:
				relationship.append([person_id[wife], husband[0], person_id[child]])



result = ""
for i in relationship:
	result += "parents(" + i[2] +", "+ i[0] +", "+ i[1] + ").\n" 
for i in person_sex:
	result += "sex(" + person_id[i] + ", " + person_sex[i] + ").\n"


prolog_text = \
"\n\
sibling(X, Y) :- parents(X, A, B), parents(Y, A, B), X\=Y.\n\
brother(X, Y) :- sibling(X, Y), sex(Y, male).\n\
sister(X, Y) :- sibling(X, Y), sex(Y, female).\n\
cousin(X, Y) :- parents(X, A, B), sibling(A, AA), parents(Y, AA, Z). \n\
cousin(X, Y) :- parents(X, A, B), sibling(A, AA), parents(Y, Z, AA). \n\
cousin(X, Y) :- parents(X, A, B), sibling(B, BB), parents(Y, BB, Z). \n\
cousin(X, Y) :- parents(X, A, B), sibling(B, BB), parents(Y, Z, BB). \n\
husband(X, Y) :- parents(A, X, Y).\n\
wife(X, Y) :- husband(Y, X).  \n\
mother(X, Y) :- parents(X, Y, Z).\n\
father(X, Y) :- parents(X, Z, Y).\n\
teshya(X, Y) :- wife(X, Z), mother(Z, Y).\n\
\n\
relative(sibling, X, Y) :- sibling(X, Y)."

ged_file.close()
prologpl = open("prolog.pl", "w")
prologpl.write(result.lower() + prolog_text)
prologpl.close()

print(result.lower() + prolog_text)
