// Write a C program that swaps two integers(in the main body of code).
#include<stdio.h>
int main(){
  int x = 5;
  int y = 42;
  int temp = x;
  printf("x: %d, y: %d\n", x, y);
  x = y;
  y = temp;
  printf("x: %d, y: %d\n", x, y);
  return 0;
}
