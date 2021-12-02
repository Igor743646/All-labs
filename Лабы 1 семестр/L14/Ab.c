#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int main() {
  int i,j,n,k;
 
  int *A;
  scanf ("%d",&n);
  A=(int*)malloc(n*n*sizeof(int));
   for (i=1; i<n+1; i++) {
      for (j=1; j<n+1; j++) {
        //printf("A[%d][%d]= ", i,j);
         scanf("%d", (A + (i-1)*n + (j-1)));
      }
   }
   for (i=1; i<n+1; i++) {
      for (j=1; j<n+1; j++) {
         
         printf("%d ", *(A + (i-1)*n + (j-1)));
         
      }
      printf ("\n");
   }
  printf ("\n");
  i=j=1;
  for (k=2; k<=n+n; k++) {
    if (k<=n+1) {i=k-1; j=1;} else {i=n; j=k-n;}
      while (i+j==k && i<=n && j<=n && i+j<k+1 && i>=1 && j>=1) {
        printf ("%d ", *(A + (i-1)*n + (j-1))); i--; j++;
      }
  }

printf ("\n");
     return 0;
}
