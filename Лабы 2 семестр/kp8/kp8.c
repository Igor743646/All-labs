
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define and &&
#define or ||

struct Item{
	struct Item *prev;
	struct Item *next;
	int value;
};

typedef struct{
	struct Item *node;
}Iterator;

typedef struct {
	struct Item *head;
	int size;
} List;


//////////////////////////////////

void Create(List *l){
	l->head=malloc(sizeof(struct Item));
	l->head->prev=l->head;
	l->head->next=NULL;
	l->size=0;
}

Iterator First(const List *l) {
	Iterator res = {l->head->next};
	return res;
}

Iterator Last(const List *l) {
	if (l->size!=0) {
	Iterator res = {l->head->next};
	while (res.node->next!=NULL) {
		res.node=res.node->next;
	}
	return res;
	} else {
		Iterator res = {l->head->prev};
		return res;
	}

}

bool Equal(const Iterator *lhs, const Iterator *rhs) {
	return lhs->node==rhs->node;
}

bool Empty(const List *l) {
	Iterator fst=First(l);
	return fst.node==NULL;
}

int SizeList(const List *l) {
	return l->size;
}

Iterator InsertNext(List *l, Iterator *i, const int x) {
	Iterator res={ malloc(sizeof(struct Item))};
	//printf("c");
	if (!res.node) {
		return Last(l);
	}
	res.node->value=x;
	//printf("c");
	res.node->next=NULL;
	//printf("c");
	res.node->prev=i->node;
	//printf("c");
	res.node->prev->next=res.node;
	//printf("c");
	l->size++;
	return res;
}

Iterator InsertByNumber(List *l, int num, int x) {
	Iterator res={ malloc(sizeof(struct Item))};
	Iterator i={ malloc(sizeof(struct Item))};
	if (!res.node) {
		return Last(l);
	}
	

	res.node=l->head->next;
	int j=1;
	while (j<num) {
		res.node=res.node->next;
		//printf("FUUUU\n");
		j++;
	}
	//printf("%d\n", res.node->value);
	if (res.node->prev!=l->head){
		res.node=res.node->prev;
		i.node->value=x;
		i.node->next=res.node->next;
		i.node->prev=res.node;
		res.node->next->prev=i.node;
		res.node->next=i.node;
		l->size++;
		return i;
	} else {
		if (res.node->prev==l->head) {
			res.node=l->head;
			i.node->value=x;
			i.node->next=res.node->next;
			i.node->prev=res.node;
			res.node->next->prev=i.node;
			l->head->next=i.node;
			l->size++;
			return i;
		}
	}
	return i;
}

Iterator Delete(List *l, Iterator i, int x) {
	if ((l->size<x) or (x<1)) {
		printf("Элемента с таким номером нет\n");
		return i;
	}

	if (l->size==1) {
		l->head->next=NULL;
		l->size--;
		return First(l);

	}


	Iterator res = {l->head->next};

	for (int i=0; i<x-1; i++) {
		res.node=res.node->next;
	}
	i.node=res.node->prev;
	if ((res.node->next != NULL) and (res.node->prev != l->head)) {
		res.node->prev->next=res.node->next;
		res.node->next->prev=res.node->prev;
		l->size--;
		free(res.node);
		res.node=NULL;
		return i;
	} else {
		if (res.node->prev != l->head) {
			res.node->prev->next=NULL;
			l->size--;
			free(res.node);
			res.node=NULL;
			return i;
		} else {
			if (res.node->next != NULL) {
				l->head->next=res.node->next;
				res.node->next->prev=l->head;
				l->size--;
				free(res.node);
				res.node=NULL;
				return i;
			} else {
				l->head->next=NULL;
				l->size--;
				free(res.node);
				res.node=NULL;
				return i;
			}
		}
	} 

	
}

void PrintList(const List *l) {
	Iterator t = {l->head->next};
	while (t.node != NULL) {
		printf("%d ", t.node->value);
		t.node=t.node->next;
	}
	printf("\n");
}

void PrintListNumber(const List *l, int x) {
	if ((l->size<x) or (x<1)){
		printf("Элемента с таким номером нет\n");

	} else {
		Iterator t = {l->head->next};
		for (int i=0; i<x-1; i++) {
			t.node=t.node->next;
		}
		printf("%d\n", t.node->value);
	}
}

void PrintListInterval(const List *l, int a, int b) {
	if ((a<=l->size) and (b<=l->size) and (a>0) and (b>0)) {
		Iterator t = {l->head->next};
		for (int i=0; i<a-1; i++) {
			t.node=t.node->next;
		}
		int i=a;
		while ((i<b) and (t.node->next!=NULL)) {
			printf("%d ", t.node->value);
			t.node=t.node->next;
			i++;
		}
		printf("%d ", t.node->value);
		printf("\n");
	} else {
		printf("Промежуток больше длины списка или элементов в данном промежутке нет\n");
	}



}



int main() {

	List l1; Iterator k;
	
	Create(&l1);

	k.node=l1.head;

	///////////////////////////////////////////////////////////////
	printf("Для вызова справки меню наберите \"1\"\n");
	while (1) {
		printf("Введите номер команды: ");
		
		int Menu;
		scanf("%d", &Menu);
		
		if ((Menu > 9) or (Menu < 0)) {
			printf("Команды с таким номером нет\n");
		}


		if (Menu == 0) {
			break;
		}

		if (Menu == 1) {
			printf("Меню:\n\t0. Выход из программы\n\t1. Меню\n\t2. Печать списка\n\t3. Печать элемента по номеру\n\t4. Печать промежутка списка\n\t5. Вставить элемент по номеру\n\t6. Вставить элемент в конец списка\n\t7. Удалить элемент по номеру\n\t8. Исключить k последних элементов списка\n\t9. Длина списка\n\n");
		}
		
		if (Menu == 2) {
			printf("Список: ");
			PrintList(&l1);
		}

		if (Menu == 3) {
			int x;
			printf("Введите номер элемента: "); scanf("%d", &x);
			PrintListNumber(&l1, x);
		}

		if (Menu == 4) {
			int a,b;
			printf("Введите a: "); scanf("%d", &a);
			printf("Введите b: "); scanf("%d", &b);
			PrintListInterval(&l1, a, b);
		}

		if (Menu == 5) {
			int num; int x;
			printf("Введите номер элемента: "); scanf("%d", &num);
			printf("Введите элемент: "); scanf("%d", &x);

			if (num>SizeList(&l1)) {
				k=Last(&l1);
				k=InsertNext(&l1, &k, x);
			} else {
				InsertByNumber(&l1, num, x);
			}

			
		}
		
		if (Menu == 6) {
			int x;
			printf("Введите элемент: "); scanf("%d", &x);
			
			k=Last(&l1);
			k=InsertNext(&l1, &k, x);
		}

		if (Menu == 7) {
			int x;
			printf("Введите номер элемента, который хотите удалить: "); scanf("%d", &x);
			k=Delete(&l1, k, x);
		}

		if (Menu == 8) {

			int kk;
			printf("Введите количество последних элементов, который хотите удалить: "); scanf("%d", &kk);
			if (kk<=SizeList(&l1)) {
				int i=0; int size=SizeList(&l1);
				while (i<kk) {
					k=Last(&l1);

					k=Delete(&l1, k, size-i);
					i++;
				}

			}

		}

		if (Menu == 9) {
			printf("Длина списка: %d\n", SizeList(&l1));
		}
	}


int i=0; int size=SizeList(&l1);
while (i<size) {
k=Last(&l1);

k=Delete(&l1, k, size-i);
i++;}
free(l1.head);

	return 0;
}