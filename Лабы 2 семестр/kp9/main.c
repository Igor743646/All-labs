#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define and &&
#define or ||

struct item {
	float key;
	char string[100];
};

int module (int a) {
	if (a>0) return a;
	else return -a;
}

void swap (struct item *table1, int x, int a) {
	float t=table1[x].key;
	char str[100]; 
	strcpy(str, table1[x].string); 
	table1[x].key=table1[a].key; 
	strcpy(table1[x].string, table1[a].string); 
	table1[a].key=t; 
	strcpy(table1[a].string, str);
}

void randomswap (struct item *table1, int a) {
	for (int i=0; i<a; i++) {
		time_t timer = time(NULL);
		int x=module((rand()*((int) timer))%(a-i));
		swap (table1, x, a-i-1);
	}
}

void print (struct item *table1, int a) {
	for (int i=0; i<a; i++) {
		printf("\t%f\t", table1[i].key);
		printf("%s", table1[i].string);
	}
}


void tour_sort (struct item *table1, const int size) {
	struct item mas[2*size-1]; struct item MIN_ELEM=table1[0];
	//Построение основания турнирного дерева и поиск минимального элемента
	// [5, 3, 7, 3, 1] -> [*, *, *, *, 5, 3, 7, 3, 1]
	for (int i=size-1; i<2*size-1; i++) {
		mas[i]=table1[i-size+1];
		if (table1[i-size+1].key<MIN_ELEM.key) {
			MIN_ELEM=table1[i-size+1];
		}
	}
	MIN_ELEM.key--; //Симулирование минус-бесконечности

	int f=0;
	int j=2*size-2;
	//Построение турнирного дерева
	// [*, *, *, *, 5, 3, 7, 3, 1] -> [7, 5, 7, 3, 5, 3, 7, 3, 1]
	while (1) {
			if (j==0) {
				break;
			}
			if (mas[j].key>mas[j-1].key) {
				mas[j/2-1]=mas[j];
			} else {
				mas[j/2-1]=mas[j-1];
			}
			j-=2;
	}

	//Поиск индекса максимального элемента и замена на минус-бесконечность
	// [7, 5, 7, 3, 5, 3, 7, 3, 1] -> [0, 5, 0, 3, 5, 3, 7, 3, 1]
	while ((2*f+1<2*size-1) and (2*f+2<2*size-1)) {
			if (mas[f].key==mas[2*f+1].key) {
				mas[f]=MIN_ELEM;
				f=2*f+1;
			} else {
				mas[f]=MIN_ELEM;
				f=2*f+2;
			}
	}
	
	//Максимальный в конец неотсортированного хвоста
	// [5, 3, 7, 3, 1] -> [5, 3, 7, 3, 7]
	table1[size-1]=mas[f];
	// [0, 5, 0, 3, 5, 3, 7, 3, 1] -> [0, 5, 0, 3, 5, 3, 0, 3, 1]
	mas[f]=MIN_ELEM;
		

	for (int s=1; s<size; s++) {
		
		//Перестроение турнирного дерева
		//// [0, 5, 0, 3, 5, 3, 0, 3, 1] -> [5, 5, 3, 3, 5, 3, 0, 3, 1]
		while (1) {
			if (f==0) {
				break;
			}
			if (f%2==0) {
				if ((mas[f].key==MIN_ELEM.key) and (mas[f-1].key==MIN_ELEM.key)) {
					f=(f>>1)-1;
				} else {
					if (mas[f].key>mas[f-1].key) {
						mas[(f>>1)-1]=mas[f];
					} else {
						mas[(f>>1)-1]=mas[f-1];
					}
					f=(f>>1)-1;
				}
			} else {
				f++;
				if ((mas[f].key==MIN_ELEM.key) and (mas[f-1].key==MIN_ELEM.key)) {
					f=(f>>1)-1;
				} else {
					if (mas[f].key>mas[f-1].key) {
						mas[(f>>1)-1]=mas[f];
					} else {
						mas[(f>>1)-1]=mas[f-1];
					}
					f=(f>>1)-1;
				}
			}
		}
	
		//Поиск индекса максимального элемента и замена на -бесконечность
		//// [5, 5, 3, 3, 5, 3, 0, 3, 1] -> [0, 0, 3, 3, 5, 3, 0, 3, 1]
		f=0;
		while ((2*f+1<2*size-1) and (2*f+2<2*size-1)) {
			if (mas[f].key==mas[2*f+1].key) {
				mas[f]=MIN_ELEM;
				f=2*f+1;
			} else {
				mas[f]=MIN_ELEM;
				f=2*f+2;
			}
		}
	
		//Максимальный в конец неотсортированного хвоста
		//// [5, 3, 7, 3, 7] -> [5, 3, 7, 5, 7]
		table1[size-1-s]=mas[f];
		//// [0, 0, 3, 3, 5, 3, 0, 3, 1] -> [0, 0, 3, 3, 0, 3, 0, 3, 1]
		mas[f]=MIN_ELEM;
	}
}

void retour_sort (struct item *table1, const int size) {
	struct item mas[2*size-1]; struct item MAX_ELEM=table1[0];
	//Построение основания турнирного дерева и поиск максимального элемента
	
	for (int i=size-1; i<2*size-1; i++) {
		mas[i]=table1[i-size+1];
		if (table1[i-size+1].key>MAX_ELEM.key) {
			MAX_ELEM=table1[i-size+1];
		}
	}
	MAX_ELEM.key++; //Симулирование плюс-бесконечности
	int f=0;
	int j=2*size-2;
	//Построение турнирного дерева
	while (1) {
			if (j==0) {
				break;
			}
			if (mas[j].key<mas[j-1].key) {
				mas[j/2-1]=mas[j];
			} else {
				mas[j/2-1]=mas[j-1];
			}
			j-=2;
		}

	//Поиск индекса минимального элемента и замена на плюс-бесконечность
		f=0;
		while ((2*f+1<2*size-1) and (2*f+2<2*size-1)) {
			if (mas[f].key==mas[2*f+1].key) {
				mas[f]=MAX_ELEM;
				f=2*f+1;
			} else {
				mas[f]=MAX_ELEM;
				f=2*f+2;
			}
		}
	
		//Минимальный в конец неотсортированного хвоста
		table1[size-1]=mas[f];
		mas[f]=MAX_ELEM;

	for (int s=1; s<size; s++) {
		//int j=2*size-2;

		//Перестроение турнирного дерева
		while (1) {
			if (f==0) {
				break;
			}
			if (f%2==0) {
				if ((mas[f].key==MAX_ELEM.key) and (mas[f-1].key==MAX_ELEM.key)) {
					f=(f>>1)-1;
				} else {
					if (mas[f].key<mas[f-1].key) {
						mas[(f>>1)-1]=mas[f];
					} else {
						mas[(f>>1)-1]=mas[f-1];
					}
					f=(f>>1)-1;
				}
			} else {
				f++;
				if ((mas[f].key==MAX_ELEM.key) and (mas[f-1].key==MAX_ELEM.key)) {
					f=(f>>1)-1;
				} else {
					if (mas[f].key<mas[f-1].key) {
						mas[(f>>1)-1]=mas[f];
					} else {
						mas[(f>>1)-1]=mas[f-1];
					}
					f=(f>>1)-1;
				}
			}
		}
	
		//Поиск индекса минимального элемента и замена на плюс-бесконечность
		f=0;
		while ((2*f+1<2*size-1) and (2*f+2<2*size-1)) {
			if (mas[f].key==mas[2*f+1].key) {
				mas[f]=MAX_ELEM;
				f=2*f+1;
			} else {
				mas[f]=MAX_ELEM;
				f=2*f+2;
			}
		}
	
		//Минимальный в конец неотсортированного хвоста
		table1[size-1-s]=mas[f];
		mas[f]=MAX_ELEM;
	}
}

void BinSearch(const struct item *table1, float fkey, int size) {
	int a=0, b=size-1;

	if ((fkey<table1[0].key) or (fkey>table1[size-1].key)) {
		printf("Такого ключа нет\n");


	} else {
	if (table1[b].key==fkey) {
		int gg=b;
		while (table1[gg-1].key==fkey) {
			gg--;
		}
		while (table1[gg].key==fkey) {
			printf("\t%f\t", table1[gg].key);
			printf("%s", table1[gg].string);
			gg++;
		}

	} else {

	while ((table1[(a+b)/2].key!=fkey) and ((a+b)/2!=a) and (a!=b)){
		if (table1[(a+b)/2].key>fkey) {
			b=(a+b)/2;
		} else {
			if (table1[(a+b)/2].key<fkey) {
				a=(a+b)/2;
			} else {
				
				break;
			}
		}
	}
	if (((a+b)!=0) and (table1[(a+b)/2].key==fkey)) {
		//printf("\t%f\t", table1[(a+b)/2].key);
		//printf("%s", table1[(a+b)/2].string);
		int gg=(a+b)/2;
		while (table1[gg-1].key==fkey) {
			gg--;
		}
		while (table1[gg].key==fkey) {
			printf("\t%f\t", table1[gg].key);
			printf("%s", table1[gg].string);
			gg++;
		}
	} else {
		printf("Такого ключа нет\n");
	}
	
	}}
}

int main() {

	struct item *table1;
	table1 = malloc(sizeof(struct item)*10);
	FILE *keyfile; FILE *poemfile;
	int SIZE_OF_TABLE; int cicle=0;
	bool SORTED=0;
	
	printf("Для вызова справки наберите \"1\"\n");
	while (1) {
		printf("Введите номер команды: ");
		
		int Menu;
		scanf("%d", &Menu);
		
		if ((Menu > 9) or (Menu < 0)) {
			printf("Команды с таким номером нет\n");
			cicle++;
			if (cicle==10) {
				return 0;
			}
		}


		if (Menu == 0) {
			break;
		}

		if (Menu == 1) {
			printf("Меню:\n\t0. Выход из программы\n\t1. Меню\n\t2. Считать из файла\n\t3. Печать таблицы\n\t4. Перемешать\n\t5. Турнирная сортировка\n\t6. Обратная турнирная сортировка\n\t7. Двоичный поиск по отсортированной таблице\n\n");
		}
		
		if (Menu == 2) {
			char filename[50];
			printf("Введите имя файла с ключами: "); scanf("%s", filename);
			getchar();
			if ((keyfile = fopen(filename, "r")) == NULL) {
    		fprintf(stderr, "Error: Файла с таким именем не существует\n"); return 0;
    		}
			keyfile = fopen(filename, "r");
			printf("Введите имя файла с данными: "); scanf("%s", filename);
			getchar();
			if ((poemfile = fopen(filename, "r")) == NULL) {
    		fprintf(stderr, "Error: Файла с таким именем не существует\n"); return 0;
    		}
			poemfile = fopen(filename, "r");

			int i=0;
			while ((!feof(keyfile)) and (!feof(poemfile))) {

				if ((i%10==0) and (i!=0)) {
					table1 = (struct item*)realloc(table1, sizeof(struct item)*(i+10));
				}
				fscanf(keyfile, "%f", &table1[i].key);
				fgets(table1[i].string, 100, poemfile);
				i++;
		
			}
			SIZE_OF_TABLE=i-1;
			//printf("%d\n", SIZE_OF_TABLE);
			fclose(keyfile);
			fclose(poemfile);
		}
		
		if (Menu == 3) {
			print(table1, SIZE_OF_TABLE);
		}

		if (Menu == 4) {
			randomswap(table1, SIZE_OF_TABLE);
			SORTED=0;
		}

		if (Menu == 5) {
			tour_sort(table1, SIZE_OF_TABLE);
			SORTED=1;
		}

		if (Menu == 6) {
			retour_sort(table1, SIZE_OF_TABLE);
			SORTED=0;
		}

		if (Menu == 7) {
			if (SORTED==1) {
				float x;
				printf("Введите ключ: "); scanf("%f", &x);
				getchar();
				BinSearch(table1, x, SIZE_OF_TABLE);
			} else {
				printf("Массив не отсортирован в порядке возрастания\n");
			}
		}

	}

	return 0;
}