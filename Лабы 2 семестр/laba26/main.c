#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#define and &&
#define or ||
#include "queue.h"
#include "sort.h"


int main() {
	queue QU;
	create(&QU, 1);
	printf("Для вызова справки меню наберите \"1\"\n");
	while (1) {
		printf("Введите номер командыыыы: ");
		
		int Menu;
		scanf("%d", &Menu);
		
		if ((Menu > 10) or (Menu < 0)) {
			printf("Команды с таким номером нет\n");
		}


		if (Menu == 0) {
			break;
		}

		if (Menu == 1) {
			printf("Меню:\n\t0. Выход из программы\n\t1. Меню\n\t2. Добавить в очередь\n\t3. Размер очереди\n\t4. Печать очереди\n\t5. Удалить из очереди\n\t6. Отправить последнего в конец\n\t7. Сортировка пузырьком по возрастанию\n\t8. Сортировка пузырьком по убыванию\n\t9. Удаление очереди\n\t10. Создать очередь из n элементов\n\n");
		}


		if (Menu == 2) {
			time_t timer = time(NULL);
			int x=(rand()*((int) timer))%100;
			load(&QU, x);
		}

		if (Menu == 3) {
			printf("Размер: %d\n", size(&QU));
		}

		if (Menu == 4) {
			printf("Очередь: "); print(&QU, size(&QU)); printf("\n");
		}

		if (Menu == 5) {
			del(&QU);
		}

		if (Menu == 6) {
			finl(&QU);
		}

		if (Menu == 7) {
			sortedqueuein(&QU);
		}

		if (Menu == 8) {
			sortedqueuede(&QU);
		}
		
		if (Menu == 9) {
			if (!empty(&QU)) {
			int s = size(&QU);
			for (int i=0; i<s; i++) {
				del(&QU);
			}} else {
				printf("Очередь уже пустая\n");
			}
		}

		if (Menu == 10) {
			if (empty(&QU)) {
				int n;
				printf("Введите количество элементов n: "); scanf("%d", &n);
				getchar();

				for (int i=0; i<n; i++) {
					time_t timer = time(NULL);
					int x=(rand()*((int) timer))%100;
					load(&QU, x);
				}
			} else {
				printf("Очередь уже создана\n");
			}
		}

	}
int s = size(&QU);
for (int i=0; i<s; i++) {
	del(&QU);
}	
return 0;
}
