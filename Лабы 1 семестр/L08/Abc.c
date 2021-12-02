
#include <stdio.h>

int main() {
  int i,j;
  int detA;
  int A[2][2];
   for (i=0; i<2; i++) {
      for (j=0; j<2; j++) {
         printf("A[%d][%d]= ", i,j);
         scanf("%d", &A[i][j]);
      }
   }
   for (i=0; i<2; i++) {
      for (j=0; j<2; j++) {
         if (j<1)
         printf("%d ", A[i][j]);
         else
         printf("%d \n", A[i][j]);
      }
   }

   detA = (A[0][0]*A[1][1]/A[1][0]);
   printf("DetA=%d", detA);


     return 0;
}
