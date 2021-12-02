#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vector.h"

void print(vector *v) {
 if (v->size!=0) {
  for (int i=0; i<v->size; i++) {
  printf("%-8.4f ", v->data[i]);
 }
  printf("\n");} else {
    printf("Матрица нулевая\n");
  }
}

void printfloat(vector *v) {
 if (v->size!=0) {
  for (int i=0; i<v->size; i++) {
  printf("%-8.0f ", v->data[i]);
 }
  printf("\n");} else {
    printf("Матрица нулевая\n");
  }
}

void print_matr (vector *v1, vector*v2,int m1,int n1) {
  printf("\t");
  float null=0;
  for (int i=0; i<m1*n1; i++) {
   
  int flag=0;
    for (int j=0; j<i+1; j++) {
      if (load(v1, j)==i) {
        printf("%9.4f ", load(v2, j)); 
        flag=1; 
        break;}}

  if (flag==0) {
    printf("%9.4f ", null);}

  if ((i+1)%n1==0) {
   printf("\n\t");}
 } 
}


int main() {
/*----------МАТРИЦА А----------*/
vector lb1; int n1,m1; 
vector ye1;
create(&lb1, 1);
save(&lb1, 0, -1);
create(&ye1, 1);
printf("\nМАТРИЦА А:\n\n");
printf("Введите m: "); scanf("%d",&m1);
  if (m1<1) {
    printf("Неправильно заданный размер\n"); 
    destroy(&lb1);
    destroy(&ye1);
    return 0;
  }
printf("Введите n: "); scanf("%d",&n1);
  if (n1<1) {
    printf("Неправильно заданный размер\n"); 
    destroy(&lb1);
    destroy(&ye1);
    return 0;
  }
{ float a1;
for (int i=1; i<m1+1; i++) {
  for (int j=1; j<n1+1; j++) {
    scanf("%f",&a1);
    if (a1!=0) {
      resize(&ye1, size(ye1)+1);
      resize(&lb1, size(lb1)+1);
      save(&ye1, size(ye1)-2, a1);
      save(&lb1, size(lb1)-2, ((i-1)*n1+j-1));
      save(&lb1, size(lb1)-1, -1);

    }
  }
} }

resize(&ye1, size(ye1)-1);

printf("\n");
printf("LB:\t"); printfloat(&lb1);
printf("YE:\t"); print(&ye1);
printf("\n");

print_matr(&lb1, &ye1, m1, n1);

/*----------МАТРИЦА В----------*/
vector lb2; int n2,m2;
vector ye2; 
create(&lb2, 1);
save(&lb2, 0, -1);
create(&ye2, 1);
printf("\nМАТРИЦА В:\n\n");
printf("Введите m: "); scanf("%d",&m2);
  if (m2<1) {
    printf("Неправильно заданный размер\n"); 
    destroy(&lb1);
    destroy(&lb2);
    destroy(&ye1);
    destroy(&ye2);
    return 0;
  }
printf("Введите n: "); scanf("%d",&n2);
  if (n2<1) {
    printf("Неправильно заданный размер\n"); 
    destroy(&lb1);
    destroy(&lb2);
    destroy(&ye1);
    destroy(&ye2);
    return 0;
  }
{  float a1;
for (int i=1; i<m2+1; i++) {
  for (int j=1; j<n2+1; j++) {
    scanf("%f",&a1);
    if (a1!=0) {
      resize(&ye2, size(ye2)+1);
      resize(&lb2, size(lb2)+1);
      save(&ye2, size(ye2)-2, a1);
      save(&lb2, size(lb2)-2, ((i-1)*n2+j-1));
      save(&lb2, size(lb2)-1, -1);

    }
  }
} }

resize(&ye2, size(ye2)-1);

printf("\n");
printf("LB:\t"); printfloat(&lb2);
printf("YE:\t"); print(&ye2);
printf("\n");

print_matr(&lb2, &ye2, m2, n2);

/*----------МАТРИЦА С----------*/
int m3,n3;

if (n1!=m2) {
  printf("\nКоличество столбцов первой матрицы должно равняться количеству строк второй!\n\n"); 
  destroy(&lb1);
  destroy(&lb2);
  destroy(&ye1);
  destroy(&ye2);
  return 0;
} else {
  m3=m1; n3=n2;
}

vector lb3;
vector ye3; 
create(&lb3, 1);
save(&lb3, 0, -1);
create(&ye3, 1);

/*----------УМНОЖЕНИЕ А на В----------*/
{int flag1=-1; int flag2=-1; float c;
for (int i=1; i<m3+1; i++) {
  for (int j=1; j<n3+1; j++) {
    c=0;
    for (int t=1; t<n1+1; t++) {
      flag1=-1; flag2=-1;
      for (int p=0; p<size(lb1); p++) {
      if (lb1.data[p]==(i-1)*n1+t-1) {
        flag1=p;}}
       for (int p=0; p<size(lb2); p++) {
      if (lb2.data[p]==(t-1)*n2+j-1) {
        flag2=p;}}
      if ((flag1>=0) && (flag2>=0)) {
      c=c+ye1.data[flag1]*ye2.data[flag2];}
      
}


if (c!=0) {
  resize(&ye3, size(ye3)+1);
  resize(&lb3, size(lb3)+1);
  save(&ye3, size(ye3)-2, c);
  save(&lb3, size(lb3)-2, ((i-1)*n3+j-1));
  save(&lb3, size(lb3)-1, -1);
}
}}}

resize(&ye3, size(ye3)-1);

printf("\n");
printf("МАТРИЦА C:\n\n");
printf("LB:\t"); printfloat(&lb3);
printf("YE:\t"); print(&ye3);
printf("\n");

print_matr(&lb3, &ye3, m3, n3);

/*----------ПРОВЕРКА НА ДИАГОНАЛЬНОСТЬ----------*/
if (m3!=n3) {
  printf ("\e[91m" ); 
  printf("\nМатрица С не диагональная\n"); 
  printf ("\e[0m" ); 
  printf ("\n" );
} else {
  int flag=0; float null=0;
  for (int i=0; i<size(lb3)-1; i++) {
    if (  ((int)lb3.data[i])%(m3+1)!=(int)null) {
      printf ("\e[91m" ); 
      printf("\nМатрица С не диагональная\n"); 
      printf ("\e[0m" ); 
      printf ("\n" ); 
      flag=1; break;
    }
  }
  if (flag==0) {
    printf ("\e[92m" );
    printf("\nМатрица С диагональная\n");
    printf ("\e[0m" );
    printf ("\n" );
  }
}
destroy(&lb1);
destroy(&lb2);
destroy(&lb3);
destroy(&ye1);
destroy(&ye2);
destroy(&ye3);
return 0;
}
