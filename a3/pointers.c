/*
  pointer.c 
  created by Wen Xie on Jan 25
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void X() {
  int a = 1;
  int b = 2;
  printf("a = %d b = %d \n", a, b);
}
void Y(int p) {
  int q;
  q = p + 2;
  printf("p = %d q = %d \n", p, q);
}

int main() {
  int a = 3;
  int b = 4;
  X();
  printf("after X(), a = %d b = %d \n", a, b);
  Y(5);
  printf("after Y(), a = %d b = %d \n", a, b);
  int i;
  int arr[3] = {3, 5, 7};
  for (i = 0; i < sizeof(arr) / sizeof(a); i++) {
    assert(arr[i] == *(arr + i));
    assert(&arr[i] == arr + i);
    printf("0x%p == 0x%p && %d == %d\n", &arr[i], arr + i, arr[i], *(arr + i));
  }
}
