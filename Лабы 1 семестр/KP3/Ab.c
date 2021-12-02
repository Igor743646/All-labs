#include <stdio.h>

#include <limits.h>

#include <math.h>

int main() {
  long double g=0.0,x=0.0,f=0.0,f0=0.0,e=0.0,N=0.0,K=0.0; int n,i,t=0,k;
  e=1.0;
  while (1.0+e/2.0>1.0) {
    e=e/2.0;}
  // printf("e=%.63Lf\n",e); 
 scanf("%d",&n);
 scanf("%d",&k);
 N=(long double) 2/n; //Ищем шаг аргумента
 printf("N=%Lf\n",N);
 K=pow(10.0, k); //Ищем коэффициент точности
 printf("K=%Lf\n",K);
 printf("Аргумент Встроенные функции       Формула Тейлора       Количество итераций    Дельта\n");
 x=0.0;
 for (i=0; i<n+1; i++) {
 printf("X=%.4Lf ", x);

 f0=pow(2.0*x-5.0, -1);
 printf("F0=%.16Lf   ",f0);
 f=0.0; g=-0.2;
 while (K*e<-g && t!=99) {
  f=f+g;
  g=(g*2.0*x)/5.0;
  t++;
 }

printf("F=%.16Lf ",f);
printf("Количество итераций: %d ",t);
printf("Дельта= %.16Lf \n", f-f0);
t=0; 
x=x+N;
}

     return 0;
}
