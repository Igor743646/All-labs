#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

int max(int x,int y) {
 if (x>=y) return x;
  else return y;
}
int sign(int x) {
  if (x>0) return 1;
   else if (x=0) return 0;
    else return -1;
}
int min(int x,int y) {
 if (x<=y) return x;
  else return y;
}
int module(int x) {
  if (x>0) return x;
   else
    return x*(-1);
}
int mod(int x, int y) {
  if (x*y<0) return (x%y+y);
   else return x%y;
} 
int main() {
  int i=8,j=15,l=10,k=0, I,J,L;
  printf("k=%d   ",k);
  printf("i[%d]=%d   ",k,i);
  printf("j[%d]=%d   ",k,j);
  printf("l[%d]=%d   ",k,l);
  if (i>=-10 && i+j-10<=0 && -i+j-10>=0) {printf("%sПопала%s \n", YELLOW, RESET); return 0;}
    else printf("%sНе попала%s \n", RED, RESET);

  for (k=0; k<50; k++) {
  I=mod((    (mod(  (i+j) , (module(min(j-l,l-k))+1)   )-k)     ) , 20) - 10;
  J=max((i+j)/(2+sign(j*l-i*k)),(j+l)/(2+sign(i*j-l*k)))-10;
  L=mod((max(i,j)*min(i,l)),30);
  i=I;
  j=J;
  l=L;
  printf("k=%d   ",k+1);
  printf("i[%d]=%d   ",k+1,i);
  printf("j[%d]=%d   ",k+1,j);
  printf("l[%d]=%d   ",k+1,l);
  if (i>=-10 && i+j-10<=0 && -i+j-10>=0) {printf("%sПопала%s \n", YELLOW, RESET); break;}
    else printf("%sНе попала%s \n", RED, RESET);
}
     return 0;
}