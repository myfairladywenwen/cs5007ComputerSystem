// Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.
#include <stdio.h>
#include <stdlib.h>
int main() {
  int* arr = (int*)malloc(sizeof(int)*400);
  assert(arr);
  (*arr) = 0;
  *(arr++) = 1;
  *(arr++) = 2;
  *(arr++) = 3;
  *(arr++) = 4;
  *(arr++) = 5;
  *(arr++) = 6;

  return 0;
}
