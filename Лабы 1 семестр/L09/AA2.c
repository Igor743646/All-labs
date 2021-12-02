#include <stdio.h>

int main() {
 int F=0;
 int m,n,i,I=-1,j,J=-1,k,K=-1,I1,J1,K1;
 printf("Введите m=");
 scanf("%d",&m);
 printf("Введите n=");
 scanf("%d",&n);
 printf("Введите i=");
 scanf("%d",&i);
 printf("Введите j=");
 scanf("%d",&j);
 printf("Введите k=");
 scanf("%d",&k);
 I1=i;
 J1=j;
 K1=k;
 while (k>0 && k<5) {
 	if (k==1) {
      
      while (i!=m && j!=n) {
        if (i!=I || j!=J || k!=K) {
       i++;
       j++;}
       else 
        {
        k=9;
        break;}
      }
      if (i==m && j==n) 
      	k=7;
        
        else
         if (i==m) 
         	k=4;
         	else
            if (j==n)
         	k=2;	
         
      
      	
      }
      
      else 
        if (k==2) {
      while (i!=m && j!=0) {
        if (i!=I || j!=J || k!=K) {
       i++;
       j-=1;}
       else
       {
        k=9;
        break;}
       
      }
      if (i==m && j==0) 
      	k=7;
        
        else
         if (i==m) 
         	k=3;
         	else
            if (j==0)
         	k=1;	
      
     
      	
      }
      


      else 
      if (k==3) {
      while (i!=0 && j!=0) {
        if (i!=I || j!=J || k!=K) {
       i-=1;
       j-=1;}
        else
          {
        k=9;
        break;}
      }
      if (i==0 && j==0) 
      	k=7;
        
        else
         if (i==0) 
         	k=2;
         	else
            if (j==0)
         	k=4;	
         
     
      	
      }

      else 

         if (k==4) {
      while (i!=0 && j!=n) {
        if (i!=I || j!=J || k!=K) {
       i-=1;
       j++;}
       else
          {
        k=9;
        break;}
      }
      if (i==0 && j==n) 
      	k=7;
       
        else
         if (i==0) 
         	k=1;
         	else
            if (j==n)
         	k=3;	
         
     
      	
       }

     
 	
 	F++;
  I=I1;
  J=J1;
  K=K1;
 }
 printf("Число ударов о стенку:%d\n", F-1);

 if (k==7) {
 if (i==0)
  if (j==0)
    printf("Первая Лунка\n");
   else 
    printf("Четвёртая Лунка\n");
  else
    if (j==0)
      printf("Вторая Лунка\n");
     else
      printf("Третья Лунка\n");}


  else
   printf("Цикл\n");

	return 0;
}