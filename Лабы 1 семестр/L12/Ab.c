#include <stdio.h>
int main() {
  long long a,b=0,i=0,k=1,t=0;
  printf("Введите число: "); scanf("%lld", &a);
  if (a<0) {
    a*=-1;
    t=1;
  }
  
  while (a>0) {
    if (i%2==0) {
      b+=(a%10)*k;
      k*=10;
    }
    a/=10;
    i++;
    
  }
  if (t==0) {
  printf ("Ответ:%lld\n",b);}
  else {b*=-1; printf ("Ответ:%lld\n",b);}
  return 0;
}
