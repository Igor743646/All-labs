#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
  char string[60]; 
  int i=0,a=0,k=0,j=0; 
  char s;
  for (i=0; i<60; i++) {string[i]='\0';} //Избавляем массив от случайного мусора
  i=0;  
  while (scanf("%c",&s) != EOF) {
    if (s == '\t' || s == ' '  || s == ',' || s==EOF) { //Если ввод слова закончился и оно записалось в массив
      /*Проверка слова на соответствия требованиям обработки*/
      if ((string[0] == '-' && (string[1] >='0' && string[1] <= '9')) || (string[0] >='0' && string[0] <= '9')) {
      j=1; 
      while (string[j] >='0' && string[j] <= '9') {
      j++;}
      if (string[j] == 'C' && string[j+1] == '\0') {
      k=1;}}
      i=0;
       
       if (k==1) { //Если введено нужное слово
       k=0;
       if (string[i] >= '0' && string[i] <= '9') { //Если число положительное
        while (string[i] != 'C') {
          a = a*10;
          a += string[i] - '0';
          i++;}
        printf("%dF ",(a*9)/5+32); //Вывод ответа
        a = 0;} 
      else { //Если число отрицательное
          i++;
          a = (a + (string[i] - '0')) * -1;
          i++;
          while (string[i] != 'C') {
           a = a*10;
           a -= string[i] - '0';
           i++;}
           printf("%dF ",(a*9)/5+32); //Вывод ответа
           a = 0; 
          }}
       else {for (i=0; i<60; i++) {printf("%c", string[i]);}printf(" ");} //Иначе вывести изначально введенное слово

    
    for (i=0; i<60; i++) {string[i] = '\0'; } //Зачистить массив
    i=0;
    //printf("\n");
    a=0;}
      else {if (s == '\n' || s == EOF) {
        if ((string[0] == '-' && (string[1] >='0' && string[1] <= '9')) || (string[0] >='0' && string[0] <= '9')) {
      j=1; 
      while (string[j] >='0' && string[j] <= '9') {
      j++;}
      if (string[j] == 'C' && string[j+1] == '\0') {
      k=1;}}
      i=0;
       
       if (k==1) { //Если введено нужное слово
       k=0;
       if (string[i] >= '0' && string[i] <= '9') { //Если число положительное
        while (string[i] != 'C') {
          a = a*10;
          a += string[i] - '0';
          i++;}
        printf("%dF ",(a*9)/5+32); //Вывод ответа
        a = 0;} 
      else { //Если число отрицательное
          i++;
          a = (a + (string[i] - '0')) * -1;
          i++;
          while (string[i] != 'C') {
           a = a*10;
           a -= string[i] - '0';
           i++;}
           printf("%dF ",(a*9)/5+32); //Вывод ответа
           a = 0; 
          }}
       else {for (i=0; i<60; i++) {printf("%c", string[i]);}printf(" ");} //Иначе вывести изначально введенное слово

    
    for (i=0; i<60; i++) {string[i] = '\0'; } //Зачистить массив
    i=0;
    //printf("\n");
    a=0;
    printf("\n");}
     else 
      
      {if (s != EOF) {string[i] = s;   //Заполняем массив введенным словом     
       i++;}}
      }}


 if ((string[0] == '-' && (string[1] >='0' && string[1] <= '9')) || (string[0] >='0' && string[0] <= '9')) {
      j=1; 
      while (string[j] >='0' && string[j] <= '9') {
      j++;}
      if (string[j] == 'C' && string[j+1] == '\0') {
      k=1;}}
      i=0;
       
       if (k==1) { //Если введено нужное слово
       k=0;
       if (string[i] >= '0' && string[i] <= '9') { //Если число положительное
        while (string[i] != 'C') {
          a = a*10;
          a += string[i] - '0';
          i++;}
        printf("%dF ",(a*9)/5+32); //Вывод ответа
        a = 0;} 
      else { //Если число отрицательное
          i++;
          a = (a + (string[i] - '0')) * -1;
          i++;
          while (string[i] != 'C') {
           a = a*10;
           a -= string[i] - '0';
           i++;}
           printf("%dF ",(a*9)/5+32); //Вывод ответа
           a = 0; 
          }}
       else {for (i=0; i<60; i++) {printf("%c", string[i]);}printf(" ");} //Иначе вывести изначально введенное слово



  
  printf("\n");
  return 0;
}
