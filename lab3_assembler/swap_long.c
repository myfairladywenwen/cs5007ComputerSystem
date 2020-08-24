// Now modify your program to swap two long's.
#include<stdio.h>
int main(){
  long x = 5;
  long y = 42;
  long temp = x;
  printf("x: %ld, y: %ld\n", x, y);
  x = y;
  y = temp;
  printf("x: %ld, y: %ld\n", x, y);
  return 0;
}
