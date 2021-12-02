#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define and &&
#define or ||


struct node {
	float num;
	struct node *l;
	struct node *r;
};
typedef struct node *tree;

tree buildtree(int n, float x) {
	tree tree=malloc(sizeof(struct node));
	 

	if (n!=0) {

	tree->num=x;
	x=(rand()%100);
	if (x>=tree->num) {
		tree->r=buildtree(n-1, x);
	} else {
		tree->l=buildtree(n-1, x);
	}} else {
		tree->num=0;
		
		return NULL;
	}
	
	return tree;
}


tree Add(tree root, float x) {
	//tree tree=malloc(sizeof(struct node));

	if (root==NULL) {
		tree tree=malloc(sizeof(struct node));
		tree->num=x;
		tree->l=NULL;
		tree->r=NULL;
		return tree;
	} else {
		if (x>=root->num) {
			if (root->r!=NULL) {
				root->r=Add(root->r, x);
			} else {
				root->r=Add(root->r, x);
			}
		} else {
			if (root->l!=NULL) {
				root->l=Add(root->l, x);
			} else {
				root->l=Add(root->l, x);
			}
		}
	}

}

tree Del(tree root, float x) {

	if (root==NULL) {
		printf("Такого элемента в дереве не найдено\n");
		return root;
	} else {
		if (x>root->num) {
			root->r=Del(root->r, x);
		} else {
			if (x<root->num) {
				root->l=Del(root->l, x);
			} else {
				if ((root->l==NULL) and (root->r==NULL)) {
					root->num=0;
					free(root);
					return NULL;
				} else {
					if ((root->l==NULL) or (root->r==NULL)) {
						if (root->l==NULL) {
							root->num=0;
							return root->r;
						} else {
							root->num=0;
							return root->l;
						}
					} else {
						tree tree=malloc(sizeof(struct node));
						struct node *res=malloc(sizeof(struct node));
						res = root;
						tree = root->r;
						if (tree->l!=NULL) {
							while (tree->l!=NULL) {
								res=tree;
								tree=tree->l;
								
							}

							if (res->l==tree) {
								res->l=tree->r;
							} else {
								res->r=NULL;
							}

							
							tree->l=root->l;
							tree->r=root->r;
						
							root->r=NULL;
							root->l=NULL;
							root->num=0;
							free(root);
							root=res;
							return tree;
						} else {
							tree->l=root->l;
							root->l=NULL;
							root->r=NULL;
							root->num=0;

							free(root);
							return tree;
						}
					}
				}
			}
		}
	}
}

tree DelAll(tree root) {
	if ((root->l!=NULL) and (root->r!=NULL)) {
	root->l=DelAll(root->l);
	root->r=DelAll(root->r);
	} else {
		if (root->l!=NULL) {
			root->l=DelAll(root->l);
		} else {
			if (root->r!=NULL) {
				root->r=DelAll(root->r);
			}  }  

		
	}
	root->l=NULL;
	root->r=NULL;
	root->num=0;
	root=NULL;
	free(root);
	return root;
}

void printtree(struct node *tree, int n) {
	if (tree!=NULL) {
		
		
		printtree(tree->r, n+1);
		for (int i=0; i<n; i++) {
			printf("  ");
		}
		printf("%f\n",tree->num);

		
		printtree(tree->l, n+1);
		
		
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

int main()
{
	int n; tree root=NULL; 
	
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
			printf("Меню:\n\t0. Выход из программы\n\t1. Меню\n\t2. Создать дерево\n\t3. Печать дерева\n\t4. Добавить элемент\n\t5. Удалить элемент\n\t6. Определить число листьев\n\t7. Удалить дерево\n\n");
		}

		if (Menu == 2) {
			if (root==NULL) { 
			int count; 
			printf("Введите количество элементов:"); scanf("%d", &count);
			for (int i=0; i<count; i++) {
			float x;
			printf("Введите элемент:"); scanf("%f", &x);
			root=Add(root, x);
			//root = buildtree(count, x);
			}} else {
				printf("Дерево уже существует\n");
			}

		}

		if (Menu == 3) {
			printtree(root, 0);
		}

		if (Menu == 4) {
			float x;
			printf("Введите элемент, который хотите добавить:"); scanf("%f", &x);
			root=Add(root, x);
		}

		if (Menu == 5) {
			float x;
			printf("Введите элемент, который хотите удалить:"); scanf("%f", &x);
			root=Del(root, x);
		}

		if (Menu == 6) {
			if (root!=NULL) {
				printf("Количество листьев дерева: %d\n", CountLeaf(root));
			} else {
				printf("Количество листьев дерева: 0\n");
			}
		}

		if (Menu == 7) {
			if (root!=NULL) {
				root=DelAll(root);
			}
		}
 
}
if (root!=NULL) {
	root=DelAll(root);
}
return 0;
}
