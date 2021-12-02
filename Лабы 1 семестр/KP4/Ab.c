#include <stdio.h>
#include <stdlib.h>


#include <math.h>


long double module (long double x) {
  if (x>0.0) {
    return x;
  }
  else {return -x;}
}
int main() {
  long double e,a=-2.0,b=-1.0,y=3.0; int k;
  e=1.0;
  while (1.0+e/2.0>1.0) {
    e=e/2.0;}
 
 while (module(a-b)>=10000000000000.0*e) {
  if ((pow(y, a)*0.6-2.3*a-3.0)*(pow(y, (a+b)/2)*0.6-2.3*(a+b)/2-3.0)>0.0) {
      //(f(y,a)*f(y,(a+b)/2.0)>0.0) { (pow(y,a)*0.6-2.3*a-3.0)*(pow(y,(a+b)/2)*0.6-2.3*(a+b)/2-3.0)>0.0
    a=(a+b)/2.0; k++;} 
    else {
      if ((pow(y, b)*0.6-2.3*b-3.0)*(pow(y, (a+b)/2)*0.6-2.3*(a+b)/2-3.0)>0.0) {b=(a+b)/2; k++;} else {break;}
    }
  }
 
 printf("Ответ: %.4Lf Итерации: %d\n", (a+b)/2,k);
     return 0;
}
