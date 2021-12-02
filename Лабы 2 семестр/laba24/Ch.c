#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define and &&
#define or ||

enum type {
	VALUE,
	VAR,
	OP,
	BR,
	UNOOP
};

union item {
	int value;
	char var;
	char operation;
	char skobki;
};

struct token {
	union item elem;
	enum type type;
};

struct stek {
	struct token ctek[20];
	int size;
};

void AddToStek(struct stek *steek, struct token *x) {
	if (x->type==2) {
		steek->ctek[steek->size].elem.operation=x->elem.operation;
		steek->ctek[steek->size].type=2;
	}
	if (x->type==3) {
		steek->ctek[steek->size].elem.skobki=x->elem.skobki;
		steek->ctek[steek->size].type=3;
	}
	if (x->type==4) {
		steek->ctek[steek->size].elem.operation=x->elem.operation;
		steek->ctek[steek->size].type=4;
	}
	steek->size++;
};

void PrintStek(struct stek *steek) {
	printf("\"\"");
	for (int i=0; i<steek->size; i++) {
		printf("%c ", steek->ctek[i].elem.operation);
	}
	printf("\"\"");
	printf("\n");
};

int SizeOfStek(struct stek *steek) {
	return steek->size;
};

void DelFromStek(struct stek *steek) {
	if (steek->size>0) {
		steek->ctek[steek->size-1].elem.operation=0;
		steek->ctek[steek->size-1].type=0;
		steek->size--;
	}
};

char LastElemOfStek(struct stek *steek) {
	return steek->ctek[steek->size-1].elem.operation;
}

enum type TypeOfLastElemOfStek(struct stek *steek) {
	return steek->ctek[steek->size-1].type;
}

struct node {
	struct token num;
	struct node *l;
	struct node *r;
};
typedef struct node *tree;

tree buildtree(struct token *x) {
	tree tree=malloc(sizeof(struct node));
	if (x->type>0) {
		tree->num.elem.operation=x->elem.operation;
	} else {
		tree->num.elem.value=x->elem.value;
	}
	tree->num.type=x->type;
	tree->r=NULL;
	tree->l=NULL;


	return tree;
}


tree Findff(tree root) {
	
	if ((root->r==NULL) and (root->l==NULL)) {
		if (root->num.type>1) {
			return root;
		} else {
			return NULL;
		}
	} else {
		if ((root->r!=NULL) and (root->l==NULL)) {
			tree tree=malloc(sizeof(struct node));
			tree = Findff(root->r);
			if (tree==NULL) {
				
				if (root->num.type!=4) {
					return root;
				} else {
					return NULL;
				}
			} else {
				return tree;
			}
		} else {
			if ((root->r!=NULL) and (root->l!=NULL)) {
				tree tree=malloc(sizeof(struct node));
				tree = Findff(root->r);
				if (tree==NULL) {
					tree = Findff(root->l);
					if (tree==NULL) {
						return NULL;
					} else {
						return tree;
					}
				} else {
					return tree;
				}
			}
		}
	}
}

void Add1(tree root, struct token *x) {
	tree tree=malloc(sizeof(struct node));
	tree = Findff(root);
	if (tree!=NULL) {
		if (tree->r==NULL) {
			tree->r=buildtree(x);
		} else {
			tree->l=buildtree(x);
		}
	}
}

void printtree(struct node *tree, int n) {
	if (tree!=NULL) {

		printtree(tree->r, n+1);
		
		for (int i=0; i<n; i++) {
			printf("  ");
		}

		if (tree->num.type==0) {
			printf(" %d\n",tree->num.elem.value);
		} else {
			printf(" %c\n",tree->num.elem.operation);
		}

		printtree(tree->l, n+1);
		
	}
}

void printtree1(struct node *tree, int n) {
	if (tree!=NULL) {
		
		if (((tree->num.type>1) and (n!=0)) or ((tree->num.type<1) and (tree->num.elem.value<0))) {
			printf("(");
		}

		printtree1(tree->l, n+1);
		
		if (tree->num.type==0) {
			printf("%d",tree->num.elem.value);
		} else {
			printf("%c",tree->num.elem.operation);
		}

	
		printtree1(tree->r, n+1);
		if (((tree->num.type>1) and (n!=0)) or ((tree->num.type<1) and (tree->num.elem.value<0))) {
			printf(")");
		}

	}
}

int CountLeaf(tree root) {
	int x=0;
	if (root!=NULL) {
		if ((root->l!=NULL) and (root->r!=NULL)) {
			x=x+CountLeaf(root->r);
			x=x+CountLeaf(root->l);
		} else {
			if (root->l!=NULL) {
				x=x+CountLeaf(root->l);
			} else {
				x=x+CountLeaf(root->r);
			}
		}

	} else {
		x=1;
	}
 	return x;
}


int main(void) {

char string[200];
struct token parsedstr[200];
struct token parsedstr2[200];

//----------------Вводим выражение----------------//
printf("Доступные символы для ввода: 0-9, a-z, A-Z, +, -, /, ^, *, (, )\n");
printf("Введите выражение: "); scanf("%s", string);

int i=0;

//----------------Проверка выражения на легкие ошибки----------------//
int sizeofstring=0;
{int lvl=0; 
while (string[i]!='\0') {
	
	if (string[i]=='(') {
		lvl++;
	}
	if (string[i]==')') {
		lvl--;
		if (lvl<0) {
			printf("Неправильно введенное выражение20\n"); return 0;
		}
	}
	i++; sizeofstring++;
}

if (lvl!=0) {
	printf("Неправильно введенное выражение19\n"); return 0;
}}

i=0;
while (string[i]!='\0') {
	
	if (i>0) {

		if (((string[i-1]=='(') and (string[i]==')')) or ((string[i-1]==')') and (string[i]=='('))) {
			printf("Неправильно введенное выражение5 \n"); return 0;
		}

		if ((string[i-1]==string[i]) and ((string[i]=='+') or (string[i]=='-') or (string[i]=='/') or (string[i]=='*') or (string[i]=='^'))) {
			printf("Неправильно введенное выражение6\n"); return 0;
		}

		if (( ((string[i]>=65) and (string[i]<=91)) or ((string[i]>=97) and (string[i]<=122))) and (((string[i-1]>=65) and (string[i-1]<=91)) or ((string[i-1]>=97) and (string[i-1]<=122)))) {
			printf("Неправильно введенное выражение (Переменные состоят из одной буквы)\n"); return 0;
		}

		if ((string[i-1]=='+') and (string[i]=='-') or (string[i-1]=='+') and (string[i]=='+') or (string[i-1]=='-') and (string[i]=='-') or (string[i-1]=='-') and (string[i]=='+')) {
			printf("Неправильно введенное выражение7 \n"); return 0;
		}
		if ((string[i-1]=='*') and (string[i]=='/') or (string[i-1]=='*') and (string[i]=='*') or (string[i-1]=='/') and (string[i]=='/') or (string[i-1]=='/') and (string[i]=='*')) {
			printf("Неправильно введенное выражение8 \n"); return 0;
		}
		if ((string[i-1]=='+') and (string[i]=='*') or (string[i-1]=='+') and (string[i]=='/') or (string[i-1]=='-') and (string[i]=='*') or (string[i-1]=='-') and (string[i]=='/')) {
			printf("Неправильно введенное выражение9 \n"); return 0;
		}
		if ((string[i-1]=='^') and (string[i]=='*') or (string[i-1]=='^') and (string[i]=='/') or (string[i-1]=='-') and (string[i]=='^') or (string[i-1]=='+') and (string[i]=='^')) {
			printf("Неправильно введенное выражение10 \n"); return 0;
		}
		if (((string[i-1]=='*') and (string[i]=='^')) or ((string[i-1]=='/') and (string[i]=='^')) or ((string[i-1]=='-') and (string[i]==')')) or ((string[i-1]=='+') and (string[i]==')'))) {
			printf("Неправильно введенное выражение11 \n"); return 0;
		}
		if (((string[i-1]=='(') and ((string[i]=='*') or (string[i]=='^') or (string[i]=='/'))) or ((string[i]==')') and ((string[i-1]=='*') or (string[i-1]=='^') or (string[i-1]=='/')))) {
			printf("Неправильно введенное выражение12\n"); return 0;
		}

	} else {
		if (i==sizeofstring-1) {
			if ((string[i-1]=='(') and (string[i]==')')) {
			printf("Неправильно введенное выражение (Пустые скобки)\n"); return 0;
			}

			if ((string[i-1]==string[i]) and ((string[i]=='+') or (string[i]=='-') or (string[i]=='/') or (string[i]=='*') or (string[i]=='^'))) {
				printf("Неправильно введенное выражение13\n"); return 0;
			}

			if (((string[i+1]=='(') or ((string[i+1]>=65) and (string[i+1]<=91)) or ((string[i+1]>=97) and (string[i+1]<=122))) and (((string[i-1]>=65) and (string[i-1]<=91)) or ((string[i-1]>=97) and (string[i-1]<=122)))) {
				printf("Неправильно введенное выражение (Переменные состоят из одной буквы)\n"); return 0;
			}

			if ((string[i]=='/') or (string[i]=='*') or (string[i]=='+') or (string[i]=='-') or (string[i]=='^')) {
				printf("Неправильно введенное выражение14\n"); return 0;
			}
		} else {
			if ((string[i]=='/') or (string[i]=='*') or (string[i]=='^')) {
				printf("Неправильно введенное выражение15\n"); return 0;
			}
		}
	}
	i++;
}

//----------------Парсинг выражения----------------//
i=0; int j=0;
while (string[i]!='\0') {
	if ((string[i]=='(') or (string[i]==')')) {
		parsedstr[j].elem.skobki = string[i]; parsedstr[j].type=3; j++;
	} else {
		if ((string[i]>=48) and (string[i]<=57)) {
			int x=0; 
			while ((string[i]>=48) and (string[i]<=57)) {
				x=10*x+(string[i]-'0');
				i++; 
			}
			//printf("%d ", x);
			parsedstr[j].elem.value = x; parsedstr[j].type=0; j++; i--;
		} else {
			if ((string[i]=='+') or (string[i]=='-') or (string[i]=='*') or (string[i]=='/') or (string[i]=='^')) {
				if ((string[i]=='+') or (string[i]=='-')) {
					if ((((string[i-1]>=48) and (string[i-1]<=57)) or ((string[i-1]>=65) and (string[i-1]<=91)) or ((string[i-1]>=97) and (string[i-1]<=122)) or (string[i-1]==')')) and (((string[i+1]>=48) and (string[i+1]<=57)) or (string[i+1]=='(') or ((string[i+1]>=65) and (string[i+1]<=91)) or ((string[i+1]>=97) and (string[i+1]<=122)))) {
						parsedstr[j].elem.operation = string[i]; parsedstr[j].type=2; j++;
					} else {
						if ((string[i+1]>=48) and (string[i+1]<=57)) {
						i++; int znak=0;
						if (string[i-1]=='+') {
							znak = 1;
						} else {
							znak=-1;
						}
						int x=0; 
						while ((string[i]>=48) and (string[i]<=57)) {
							x=10*x+(string[i]-'0');
							i++; 
						}
						parsedstr[j].elem.value = znak*x; parsedstr[j].type=0; j++; i--;
					} else { 
						if ((string[i+1]=='(') or ((string[i+1]>=65) and (string[i+1]<=91)) or ((string[i+1]>=97) and (string[i+1]<=122))) {
							if (string[i]=='-') {
								parsedstr[j].elem.operation = string[i]; parsedstr[j].type=4; j++;
							}

						} else {
							parsedstr[j].elem.operation = string[i]; parsedstr[j].type=2; j++;
						}
					}
					}
				} else {
					parsedstr[j].elem.operation = string[i]; parsedstr[j].type=2; j++;
				}
				//parsedstr[j].elem.operation = string[i]; parsedstr[j].type=2; j++;
			} else {
				if (((string[i]>=65) and (string[i]<=91)) or ((string[i]>=97) and (string[i]<=122))) {
				
				parsedstr[j].elem.var=string[i];
				parsedstr[j].type=1; j++;
				} else {
					printf("Неправильно введенное выражение\n"); return 0;
				}
			}
		}
	}
	i++;
}

//----Вывод парсированного массива----// 
i=0;
for (int i=0; i<j; i++) {
	if (i>0) {
		if ((parsedstr[i-1].type==2) and (parsedstr[i].type==0)) {
			if ((parsedstr[i-1].elem.operation=='/') and (parsedstr[i].elem.value==0)) {
				printf("Деление на ноль\n"); return 0;
			}
		}
	}
}

const int SIZE_PARSEDSTR=j;

//printf("\n");

//----Алгоритм сортировочной машины----//
struct stek steek; steek.size=0;
struct stek steek1; steek1.size=0;
j=0;
for (int i=0; i<SIZE_PARSEDSTR; i++) {

	if (parsedstr[i].type==0) {
		//printf("%d ", parsedstr[i].elem.value);
		parsedstr2[j].elem.value=parsedstr[i].elem.value; parsedstr2[j].type=0; j++;
	}

	if (parsedstr[i].type==1) {
		//printf("%c ", parsedstr[i].elem.var);
		parsedstr2[j].elem.var=parsedstr[i].elem.var; parsedstr2[j].type=1; j++;
		
	}

	if (parsedstr[i].type==3) {
		if (parsedstr[i].elem.skobki=='(') {
			AddToStek(&steek, &parsedstr[i]);
		} else {
			while (LastElemOfStek(&steek)!='(') {
				//printf("%c ", LastElemOfStek(&steek));
				parsedstr2[j].elem.operation=LastElemOfStek(&steek); parsedstr2[j].type=TypeOfLastElemOfStek(&steek); j++;
				DelFromStek(&steek);
				
			}
			
			DelFromStek(&steek);
			
		}
	}

	if (parsedstr[i].type==2) {
		int flag=0;

		while ((LastElemOfStek(&steek)!='(') and (steek.size!=0)){
			if (((LastElemOfStek(&steek)=='*') and (parsedstr[i].elem.operation=='+')) or ((LastElemOfStek(&steek)=='-') and (parsedstr[i].elem.operation=='+')) or ((LastElemOfStek(&steek)=='/') and (parsedstr[i].elem.operation=='+')) or ((LastElemOfStek(&steek)=='*') and (parsedstr[i].elem.operation=='-')) or ((LastElemOfStek(&steek)=='/') and (parsedstr[i].elem.operation=='-')) or ((LastElemOfStek(&steek)==parsedstr[i].elem.operation) and (parsedstr[i].elem.operation!='^') and (LastElemOfStek(&steek)!='^')) or ((LastElemOfStek(&steek)=='^') and (parsedstr[i].elem.operation!='^'))) {
				//printf("%c ", LastElemOfStek(&steek));
				parsedstr2[j].elem.operation=LastElemOfStek(&steek); parsedstr2[j].type=TypeOfLastElemOfStek(&steek); j++;
				DelFromStek(&steek);
				//printf("%d \n", steek1.size);
				
			} else {
				AddToStek(&steek, &parsedstr[i]);
				flag=1;
				break;
			}}
			if (flag==0) {
				AddToStek(&steek, &parsedstr[i]);
			}

		}
	
	if (parsedstr[i].type==4) {
		//printf("%d \n", steek.size);
		//printf("type: %d\n", parsedstr[i].type);
		int flag=0;

		while ((LastElemOfStek(&steek)!='(') and (steek.size!=0)){
			if (((TypeOfLastElemOfStek(&steek)<4) and (LastElemOfStek(&steek)!='^')) or ((LastElemOfStek(&steek)==parsedstr[i].elem.operation) and (parsedstr[i].elem.operation!='^') and (LastElemOfStek(&steek)!='^'))) {
				//printf("%c ", LastElemOfStek(&steek));
				parsedstr2[j].elem.operation=LastElemOfStek(&steek); parsedstr2[j].type=4; j++;
				DelFromStek(&steek);
				//printf("%d \n", steek1.size);
				
			} else {
				AddToStek(&steek, &parsedstr[i]);
				flag=1;
				break;
			}}
			if (flag==0) {
				AddToStek(&steek, &parsedstr[i]);
			}
	}
	//PrintStek(&steek1);
}

while (steek.size!=0) {
		//printf("%c ", LastElemOfStek(&steek));
		parsedstr2[j].elem.operation=LastElemOfStek(&steek); parsedstr2[j].type=TypeOfLastElemOfStek(&steek);  j++;
		DelFromStek(&steek);
}


//----Вывод постфиксной формы массива----//
printf("Постфиксная форма выражения: ");
i=0;
for (int i=0; i<j; i++) {
	if (parsedstr2[i].type==0) {
		printf("%d ", parsedstr2[i].elem.value);
	} else {
		
		printf("%c ", parsedstr2[i].elem.var);
		
	}
}
printf("\nДерево выражения: \n");

const int SIZE_PARSEDSTR1=j;



//----Построение дерева выражения----//
tree root=NULL;
//printf("type: %d\n", parsedstr2[2].type);
root=buildtree(&parsedstr2[SIZE_PARSEDSTR1-1]);


for (int i=0; i<SIZE_PARSEDSTR1-1; i++) {
	Add1(root, &parsedstr2[SIZE_PARSEDSTR1-i-2]);
}

printtree(root, 0);
//printf("----------");
printf("Исходное выражение: ");
printtree1(root, 0);
printf("\n");
printf("Количество операндов: %d\n", CountLeaf(root));
return 0;
}

