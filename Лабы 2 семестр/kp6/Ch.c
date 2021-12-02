#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct
  {
    int number;
    char surname[256];
    char name_father[8];
    int count_bagged;
    int pound;
    char punkt[64];
    int hour;
    int min;
    char peresadka[8];
    int child;
  } record;

int num (char *x) {
  int i=0;
  while (x[i]!='\0') {
    i++;
  }
  return i;
 }

int main(int argc, char *argv[]) { 
 
  FILE *base; FILE *fake;
  char s[80]; char snull[3] = "\n"; 
  char *file; 
  record r; 
  char *key11 = "-p"; char *key12 = "--print";
  char *key21 = "-a"; char *key22 = "--add";
  char *key31 = "-rsn"; char *key32 = "--reqstrnum";
  char *key41 = "-re"; char *key42 = "-d"; char *key43 = "--remove"; char *key44 = "--delete";
  char *key5 = "--help";
  char *key61 = "-cb"; char *key62 = "-bb"; char *key63 = "--crebase"; char *key64 = "--buibase";
  char *key71 = "-db"; char *key72 = "-reb"; char *key73 = "--delbase"; char *key74 = "--rembase";
  char *key81 = "--task"; char *key82 = "-ta";
  char *key91 = "-rss"; char *key92 = "--reqstrsur";
  int x; int y; int addnumber; int flag=0;
  int a,b=0; int k=0;

//Если пропущены ключи и операнды
if(argc==1){
 printf("Неправильный синтаксис команды. По ключу --help можно узнать подробную информацию\n");
 return 1;} 
 else {
  if ((argc>1) && (argv[1][0] != '-')) {printf("Неправильный синтаксис команды. По ключу --help можно узнать подробную информацию\n");
  return 1;}}

//Меню
if (strcmp(argv[1], key5)==0) {
  printf("Синтаксис: ./a.out [ключ] [имя_файла]\n");
  printf("Опции:\n");
  printf("1. Меню\t\t\t\t--help\n2. Запрос\t\t\t-p, --print\n3. Запрос строки по номеру\t-rsn, --reqstrnum\n4. Запрос строки по фамилии\t-rss, --reqstrsur\n5. Добавить в базу\t\t-a, --add\n6. Удалить из базы\t\t-d, -re, --remove,--delete\n7. Удалить базу\t\t\t-reb, -db, --delbase, --rembase\n8. Создать базу\t\t\t-cb, -bb, --crebase, --buibase\n9. Выполнение задания\t\t-ta, --task (Найти пассажиров, число вещей которых превосходит среднее число вещей не менее, чем на p штук)\n"); k=1;}

//Добавить строку -a
if ((argc==3) && ( (strcmp(argv[1], key21)==0 ) || (strcmp(argv[1], key22)==0)))  {
  k=1;

  while (flag==0) {

   if ((base = fopen(argv[2], "r")) == NULL) {
   fprintf(stderr, "Error: Базы с таким именем не существует\n");
   return 0;}

  base = fopen(argv[2], "r");
  fscanf(base, "%d", &a);
  while (1) {
  file = fgets(s,80,base);
  if (file == NULL) {
        if ( feof (base) != 0)
         {break;}
        else
         {printf ("\nОшибка чтения из файла\n");break;}}
  fscanf(base, "%d", &r.number); 
  if (r.number==2) {
    b=1;}}

  fclose(base);
  if ((a==1) && (b==1)) {
  r.number++; 
  } else {
    if (a==1) {
    r.number=2;
  } else {
    r.number=1;}}

  printf("\nНомер: %d\n\n", r.number);
  printf("Фамилия: "); scanf("%s", r.surname); printf("\n");
  printf("Инициалы: "); scanf("%s", r.name_father); printf("\n");
  printf("Количество сумок: "); scanf("%d", &r.count_bagged); printf("\n");
  printf("Вес багажа: "); scanf("%d", &r.pound); printf("\n");
  printf("Пункт назначения: "); scanf("%s", r.punkt); printf("\n");
  printf("Время вылета (часы): "); scanf("%d", &r.hour); printf("\n");
  printf("Время вылета (минуты): "); scanf("%d", &r.min); printf("\n");
  printf("Наличие пересадки (Да/Нет): "); scanf("%s", r.peresadka); printf("\n");
  printf("Сведение о детях: "); scanf("%d", &r.child); printf("\n");
  
  base = fopen(argv[2], "a");
  fprintf(base, "%d %s %s %d %d %s %d %d %s %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
  fclose(base);
 
  printf("Продолжить добавлять в базу?: "); scanf("%s", s);
    if ((strcmp(s, "No")==0) || (strcmp(s, "N")==0) || (strcmp(s, "Нет")==0) || (strcmp(s, "Н")==0) || (strcmp(s, "Not")==0) || (strcmp(s, "not")==0) || (strcmp(s, "no")==0) || (strcmp(s, "n")==0) || (strcmp(s, "н")==0) || (strcmp(s, "нет")==0)) {
    flag=1;}
    if ((strcmp(s, "Yes")==0) || (strcmp(s, "Y")==0) || (strcmp(s, "Да")==0) || (strcmp(s, "Д")==0) || (strcmp(s, "да")==0) || (strcmp(s, "д")==0) || (strcmp(s, "yes")==0) || (strcmp(s, "y")==0) ) { 
    flag=0;}

  }} else {
    if ((argc>3) && ( (strcmp(argv[1], key21)==0 ) || (strcmp(argv[1], key22)==0))) {
    printf("Error: Нельзя обращаться к нескольким базам одновременно\n"); k=1;
  } else {
    if ((argc==2) && ( (strcmp(argv[1], key21)==0 ) || (strcmp(argv[1], key22)==0))) {
    printf("Error: Пропущен операнд после ключа %s\n", argv[1]); k=1;}}}

//Запрос на всю базу -r
if ((argc==3) && ((strcmp(argv[1], key11) == 0) || (strcmp(argv[1], key12) == 0))) {
    k=1;
    if ((base = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "Error: Базы с таким именем не существует\n");
    return 0;}
    
    base = fopen(argv[2], "rt");
    fscanf(base, "%d", &r.number);
    if (r.number!=1) {
      printf("Error: База пуста\n");
      return 0;}
    fclose(base);

    printf("    № \t|  Фамилия\t\t| И.О. | Кол. сумок | Вес багажа | Пункт назначения | Время вылета | Наличие пересадки | Сведенья о детях\n");
    base = fopen(argv[2], "rt");
    while (1) {
    file = fgets(s,80,base);
     if (file == NULL) {
        if ( feof (base) != 0) {printf ("\n"); return 0;}
         else {printf ("\nОшибка чтения из файла\n"); return 0;}}

    fscanf(base, "%d %s %s %d %d %s %d %d %s %d", &r.number, r.surname, r.name_father, &r.count_bagged, &r.pound, r.punkt, &r.hour, &r.min, r.peresadka, &r.child);
    if ((r.number != x) && (num(r.surname)<11)) {
    printf("%5d\t   %-20s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
    } else {
      if ((r.number != x) && (num(r.surname)>=11) && (num(r.punkt)>=11)) {
      printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-25s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
    } else {
      if ((r.number != x) && (num(r.surname)>=11) && (num(r.punkt)<11)) {
      printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child); 
      }}}

    x=r.number; }
    fclose(base); 
    } else {
      if ((argc>3) && ((strcmp(argv[1], key11) == 0) || (strcmp(argv[1], key12) == 0))) {
      printf("Error: Можно сделать запрос только одной базы\n"); k=1;
    } else {
      if ((argc==2) && ((strcmp(argv[1], key11) == 0) || (strcmp(argv[1], key12) == 0))) {
      printf("Error: Пропущен операнд после ключа %s\n", argv[1]); k=1;}}}

//Запрос на определенную строку -rsn
if ((argc==3) && ((strcmp(argv[1], key31)==0) || (strcmp(argv[1], key32)==0))) {
      k=1;
      if ((base = fopen(argv[2], "r")) == NULL) {
      fprintf(stderr, "Error: Базы с таким именем не существует\n");
      return 0;}

      base = fopen(argv[2], "rt");
      fscanf(base, "%d", &r.number);
      if (r.number!=1) {
      printf("Error: База пуста\n");
      return 0;}
      fclose(base);

      printf("Введите номер строки: "); scanf("%d", &y); printf("\n");
      
      base = fopen(argv[2], "rt");
      while (1) {
        
      file = fgets(s,80,base);
      if (file == NULL) {
        if ( feof (base) != 0)
         {printf ("Error: Сроки с таким номер не было найдено\n\n"); return 0;}
         else
         {printf ("\nОшибка чтения из файла\n"); return 0;}}

      fscanf(base, "%d %s %s %d %d %s %d %d %s %d", &r.number, r.surname, r.name_father, &r.count_bagged, &r.pound, r.punkt, &r.hour, &r.min, r.peresadka, &r.child);

      if (y==r.number) {
      printf("    № \t|  Фамилия\t\t| И.О. | Кол. сумок | Вес багажа | Пункт назначения | Время вылета | Наличие пересадки | Сведенья о детях\n");
      if ((num(r.surname)<11)) {
      printf("%5d\t   %-20s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      } else {
      if ((num(r.surname)>=11) && (num(r.punkt)>=11)) {
      printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-25s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      } else {
      if ((num(r.surname)>=11) && (num(r.punkt)<11)) {
      printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child); 
      }}}
      printf("\n"); break;}}
      fclose(base); 
      } else {
        if ((argc>3) && ((strcmp(argv[1], key31)==0) || (strcmp(argv[1], key32)==0))) {
        printf("Error: Можно сделать запрос только одной базы\n"); k=1;
      } else {
        if ((argc==2) && ((strcmp(argv[1], key31)==0) || (strcmp(argv[1], key32)==0))) {
        printf("Error: Пропущен операнд после ключа %s\n", argv[1]); k=1;}}}

//Удаление строки -re
if ((argc==3) && ((strcmp(argv[1], key41)==0) || (strcmp(argv[1], key42)==0) || (strcmp(argv[1], key43)==0) || (strcmp(argv[1], key44)==0))) {
      k=1;
      if ((base = fopen(argv[2], "r")) == NULL) {
      fprintf(stderr, "Error: Базы с таким именем не существует\n");
      return 0;}

      base = fopen(argv[2], "rt");
      fscanf(base, "%d", &r.number);
      if (r.number!=1) {
      printf("Error: База пуста\n");
      return 0;}
      fclose(base);

      printf("Введите номер строки: "); scanf("%d", &y);  y--;

      if (y<-1) {
       printf("Номер строки может быть только положительным, начиная с '1' (Ввод '0' удалит всю базу)\n"); return 0;
      } else {
        if (y==-1) {
        printf("Вы уверены, что хотите удалить базу %s?: ", argv[2]); scanf("%s", s);
        if ((strcmp(s, "No")==0) || (strcmp(s, "N")==0) || (strcmp(s, "Нет")==0) || (strcmp(s, "Н")==0) || (strcmp(s, "Not")==0) || (strcmp(s, "not")==0) || (strcmp(s, "no")==0) || (strcmp(s, "n")==0) || (strcmp(s, "н")==0) || (strcmp(s, "нет")==0)) {
        return 0;}
        if ((strcmp(s, "Yes")==0) || (strcmp(s, "Y")==0) || (strcmp(s, "Да")==0) || (strcmp(s, "Д")==0) || (strcmp(s, "да")==0) || (strcmp(s, "д")==0) || (strcmp(s, "yes")==0) || (strcmp(s, "y")==0) ) {
        if(remove(argv[2])) {
         printf("Error: Удаление базы невозможно или ее не существует\n");
         return 1;
        } else {
          printf("База %s была успешно удалена\n", argv[2]); return 0;}}}}

      base = fopen(argv[2], "rt");
      fake = fopen("fake.txt", "w");
      fprintf(fake, "\n");
      fclose(fake);

      while (1) { //Удаление строки в левом файле
      file = fgets(s,80,base);
      fscanf(base, "%d %s %s %d %d %s %d %d %s %d", &r.number, r.surname, r.name_father, &r.count_bagged, &r.pound, r.punkt, &r.hour, &r.min, r.peresadka, &r.child);
      if (file == NULL) {
        if (feof (base) != 0)
         {break;}
         else
         {break;}}

      if ((y!=0) && (y>0)) {
      fake = fopen("fake.txt", "a");
      fprintf(fake, "%d %s %s %d %d %s %d %d %s %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      fclose(fake);
      } else {
        if (y!=0){
        fake = fopen("fake.txt", "a");
        if ((r.number != x) || (r.number==2)) {
        fprintf(fake, "%d %s %s %d %d %s %d %d %s %d\n", r.number-1, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child); } x=r.number; 
        fclose(fake);}}
      y--;}

      fclose(fake);
      fclose(base); 
      a=r.number;

      base = fopen(argv[2], "w"); //Удаление прошлой базы
      fprintf(base, "%s", snull);
      fclose(base);

      fake = fopen("fake.txt", "rt");
      while (1) { //Копирование с удаленной строкой
      file = fgets(s,80,fake);
      fscanf(fake, "%d %s %s %d %d %s %d %d %s %d", &r.number, r.surname, r.name_father, &r.count_bagged, &r.pound, r.punkt, &r.hour, &r.min, r.peresadka, &r.child);
      if (r.number == 0) {
       base = fopen(argv[2], "w");
       fprintf(base, "%s", snull);
       fclose(base);
       printf("\nСтрока была успешно удалена\n\n");
       if ((fake = fopen("fake.txt", "r")) != NULL) {
       remove("fake.txt");}
       return 0;} 

      if (file == NULL) {
        if ( feof (fake) != 0)
        {printf ("\n"); break;}
         else
        {break;}}
      
      base = fopen(argv[2], "a");
    
      if (r.number != x) {
      fprintf(base, "%d %s %s %d %d %s %d %d %s %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      } x=r.number;
      fclose(base);}
      fclose(fake);

       if ((fake = fopen("fake.txt", "r")) != NULL) {
       remove("fake.txt");}
       fclose(fake);
       b=r.number;
       if (a==b) {
       printf("Error: Строки под таким номером в базе нет\n"); 
       } else {printf("Строка была успешно удалена\n\n");}

       } else {
         if ((argc>3) && ((strcmp(argv[1], key41)==0) || (strcmp(argv[1], key42)==0) || (strcmp(argv[1], key43)==0) || (strcmp(argv[1], key44)==0))) {
         printf("Error: Можно сделать запрос только одной базы за раз\n"); k=1;
       } else {
         if ((argc==2) && ((strcmp(argv[1], key41)==0) || (strcmp(argv[1], key42)==0) || (strcmp(argv[1], key43)==0) || (strcmp(argv[1], key44)==0))) {
         printf("Error: Пропущен операнд после ключа %s\n", argv[1]); k=1;}}}

//Создание базы данных -cb
if ((argc==3) && ((strcmp(argv[1], key61)==0) || (strcmp(argv[1], key62)==0) || (strcmp(argv[1], key63)==0) || (strcmp(argv[1], key64)==0))) {
     k=1;
     if ((base = fopen(argv[argc-1], "r")) != NULL) {
     fprintf(stderr, "Error: База с таким именем уже существует\n");
     return 0;}

     base = fopen(argv[2], "w");
     fprintf(base, "\n");
     fclose(base);

     printf("База %s создана\n", argv[2]);
     } else {
       if ((argc>3) && ((strcmp(argv[1], key61)==0) || (strcmp(argv[1], key62)==0) || (strcmp(argv[1], key63)==0) || (strcmp(argv[1], key64)==0))) {
       printf("Error: Может быть создана только одна база за раз\n"); k=1;
     } else {
       if ((argc==2) && ((strcmp(argv[1], key61)==0) || (strcmp(argv[1], key62)==0) || (strcmp(argv[1], key63)==0) || (strcmp(argv[1], key64)==0))) {
       printf("Error: Пропущен операнд после ключа %s\n", argv[1]); k=1;}}}

//Удаление базы -db
if ((argc==3) && ((strcmp(argv[1], key71)==0) || (strcmp(argv[1], key72)==0) || (strcmp(argv[1], key73)==0) || (strcmp(argv[1], key74)==0))) {
    k=1;
    printf("Вы уверены, что хотите удалить базу %s?: ", argv[2]); scanf("%s", s);
    if ((strcmp(s, "No")==0) || (strcmp(s, "N")==0) || (strcmp(s, "Нет")==0) || (strcmp(s, "Н")==0) || (strcmp(s, "Not")==0) || (strcmp(s, "not")==0) || (strcmp(s, "no")==0) || (strcmp(s, "n")==0) || (strcmp(s, "н")==0) || (strcmp(s, "нет")==0)) {
    return 0;}
    if ((strcmp(s, "Yes")==0) || (strcmp(s, "Y")==0) || (strcmp(s, "Да")==0) || (strcmp(s, "Д")==0) || (strcmp(s, "да")==0) || (strcmp(s, "д")==0) || (strcmp(s, "yes")==0) || (strcmp(s, "y")==0) ) {
    if(remove(argv[2])) {
       printf("Error: Удаление базы невозможно или ее не существует\n");
       return 1;
    } else {
      printf("База %s была успешно удалена\n", argv[2]); return 0;}}
    } else {
      if ((argc>3) && ((strcmp(argv[1], key71)==0) || (strcmp(argv[1], key72)==0) || (strcmp(argv[1], key73)==0) || (strcmp(argv[1], key74)==0))) {
      printf("Error: Можно удалить только одну базу за раз\n"); k=1;
    } else {if ((argc==2) && ((strcmp(argv[1], key71)==0) || (strcmp(argv[1], key72)==0) || (strcmp(argv[1], key73)==0) || (strcmp(argv[1], key74)==0))){
      printf("Error: Пропущен операнд после ключа %s\n", argv[1]); k=1;}}}
  
//Задание -ta
if ((argc==3) && ((strcmp(argv[1], key81)==0) || (strcmp(argv[1], key82)==0))) {
  k=1;
  if ((base = fopen(argv[2], "r")) == NULL) {
  fprintf(stderr, "Error: Базы с таким именем не существует\n");
  return 0;}

  base = fopen(argv[2], "rt");
  fscanf(base, "%d", &r.number);
  if (r.number!=1) {
  printf("Error: База пуста\n");
  return 0;}
  fclose(base);
  
  printf("Введите значение р: "); scanf("%d", &y); 
  base = fopen(argv[2], "r");
  while (1) {
  file = fgets(s,80,base);
  if (file == NULL) {
    if ( feof (base) != 0)
      {printf ("\n"); printf("Ср кол багажа: %d\n", b/r.number); a=b/r.number; break;}
       else
      {printf ("\nОшибка чтения из файла\n"); break;}}

  fscanf(base, "%d %s %s %d %d %s %d %d %s %d", &r.number, r.surname, r.name_father, &r.count_bagged, &r.pound, r.punkt, &r.hour, &r.min, r.peresadka, &r.child);
  if (r.number != x) {
  b+=r.count_bagged;
  } x=r.number;} 
  fclose(base); x=0;

  printf("    № \t|  Фамилия\t\t| И.О. | Кол. сумок | Вес багажа | Пункт назначения | Время вылета | Наличие пересадки | Сведенья о детях\n");
  base = fopen(argv[2], "r");
  while (1) {
  file = fgets(s,80,base);
    if (file == NULL) {
        if ( feof (base) != 0)
         {printf ("\n"); break;}
          else
         {printf ("\nОшибка чтения из файла\n"); break;}}

  fscanf(base, "%d %s %s %d %d %s %d %d %s %d", &r.number, r.surname, r.name_father, &r.count_bagged, &r.pound, r.punkt, &r.hour, &r.min, r.peresadka, &r.child);
    
  if ((r.number != x) && (r.count_bagged >= y+a)) {
  //printf("%5d\t   %-24s\t  %5s\t %d\t      %d\t   %-24s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
  if ((num(r.surname)<11)) {
      printf("%5d\t   %-20s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      } else {
      if ((num(r.surname)>=11) && (num(r.punkt)>=11)) {
      printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-25s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      } else {
      if ((num(r.surname)>=11) && (num(r.punkt)<11)) {
      printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child); 
      }}}
  }x=r.number;} 
  fclose(base);

  } else {
    if ((argc>3) && ((strcmp(argv[1], key81)==0) || (strcmp(argv[1], key82)==0))) {
    printf("Error: Можно сделать запрос только одной базы\n"); k=1;
  } else {
    if ((argc==2) && ((strcmp(argv[1], key81)==0) || (strcmp(argv[1], key82)==0))){
    printf("Error: Пропущен операнд после ключа %s\n", argv[1]); k=1;}}}

//Поиск по фамилии -rss
if ((argc==3) && ((strcmp(argv[1], key91)==0) || (strcmp(argv[1], key92)==0))) {
    a=0; k=1;
    if ((base = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "Error: Базы с таким именем не существует\n");
    return 0;}

    base = fopen(argv[2], "rt");
    fscanf(base, "%d", &r.number);
    if (r.number!=1) {
    printf("Error: База пуста\n");
    return 0;}
    fclose(base);

    char surname[256];
    printf("Введите фамилию: "); scanf("%s", surname); printf("\n");

    base = fopen(argv[2], "rt");
    while (1) {
    file = fgets(s,80,base);
      if (file == NULL) {
        if ( feof (base) != 0)
         {if (a==0) {printf("Строки с такой фамилией не было найдено\n");} printf ("\n"); break;}
          else
         {printf ("\nОшибка чтения из файла\n"); break;}}

    fscanf(base, "%d %s %s %d %d %s %d %d %s %d", &r.number, r.surname, r.name_father, &r.count_bagged, &r.pound, r.punkt, &r.hour, &r.min, r.peresadka, &r.child);

      if ((strcmp(r.surname, surname)==0) && (x!=r.number) && (a==0))  {
      printf("    № \t|  Фамилия\t\t| И.О. | Кол. сумок | Вес багажа | Пункт назначения | Время вылета | Наличие пересадки | Сведенья о детях\n");
      //printf("%5d\t   %-22s\t  %5s\t %d\t      %d\t   %-24s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      if ((num(r.surname)<11)) {
      printf("%5d\t   %-20s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      } else {
      if ((num(r.surname)>=11) && (num(r.punkt)>=11)) {
      printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-25s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
      } else {
      if ((num(r.surname)>=11) && (num(r.punkt)<11)) {
      printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child); 
      }}}
      a=1;
      } else {
        if ((strcmp(r.surname, surname)==0) && (x!=r.number)) {
        //printf("%5d\t   %-22s\t  %5s\t %d\t      %d\t   %-24s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
        if ((num(r.surname)<11)) {
        printf("%5d\t   %-20s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
        } else {
        if ((num(r.surname)>=11) && (num(r.punkt)>=11)) {
        printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-25s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child);
        } else {
        if ((num(r.surname)>=11) && (num(r.punkt)<11)) {
        printf("%5d\t   %-25s\t  %-5s\t %d\t      %-2d\t   %-20s\t %02d:%02d\t     %-5s\t\t %d\n", r.number, r.surname, r.name_father, r.count_bagged, r.pound, r.punkt, r.hour, r.min, r.peresadka, r.child); 
        }}}
        a=1;}} x=r.number;}
    fclose(base);
    } else {
      if ((argc>3) && ((strcmp(argv[1], key91)==0) || (strcmp(argv[1], key92)==0))) {
      printf("Error: Можно сделать запрос только одной базы\n"); k=1;
    } else {
      if ((argc==2) && ((strcmp(argv[1], key91)==0) || (strcmp(argv[1], key92)==0))) {
      printf("Error: Пропущен операнд после ключа %s\n", argv[1]); k=1;}}}

if (k==0) {
printf("Неправильный синтаксис команды. Ключа %s не существует. По ключу --help можно узнать подробную информацию\n", argv[1]); }

return 0;
} 