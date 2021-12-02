#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int main() {
  int i,j,n,k,t,sum=0;
  int b=0;
  int *A;
  scanf ("%d",&n);
  A=(int*)malloc(n*n*sizeof(int));
   for (i=1; i<n+1; i++) {
      for (j=1; j<n+1; j++) {
        //printf("A[%d][%d]= ", i,j);
         scanf("%d", (A + (i-1)*n + (j-1)));
         if (*(A + (i-1)*n + (j-1))<b) {b=*(A + (i-1)*n + (j-1));} else {if (i==1 && j==1) {b=*(A + (i-1)*n + (j-1));}}
      }
   }
   for (i=1; i<n+1; i++) {
      for (j=1; j<n+1; j++) {
         
         printf("%d ", *(A + (i-1)*n + (j-1)));
         
      }
      printf ("\n");
   }
  printf ("\n");
   for (j=1; j<n+1; j++) {
    sum=0;
      for (i=1; i<n+1; i++) {
       if (*(A + (i-1)*n + (j-1))==b) { 
        if (sum==0) {
        for (t=1; t<n+1; t++) {sum=sum+*(A + (t-1)*n + (j-1));}}
        *(A + (i-1)*n + (j-1))=sum; 
       }
      }}
  for (i=1; i<n+1; i++) {
      for (j=1; j<n+1; j++) {
         
         printf("%d ", *(A + (i-1)*n + (j-1)));
         
      }
      printf ("\n");
   }

printf ("\n");
     return 0;
}
