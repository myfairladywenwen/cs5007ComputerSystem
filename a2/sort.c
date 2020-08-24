#include <stdio.h>
#include "sort.h"

void Sort(int* array, int length) {
  int left = length/2;
  int counter = 0;
  while (left > 0) {
    int q = length/2;
    int r = 0;
    int gap = left;
    while (q >= left) {
      for (int i = 0; i < length - gap; i++) {
        if ((i & left) == r) {
          counter++;
          if (array[i] > array[i+gap]) {
            int temp = array[i];
            array[i] = array[i+gap];
            array[i+gap] = temp;
          }
        }
      }
      gap = q - left;
      q /= 2;
      r = left;
    }
    left /= 2;
  }
  if (length < 1024) {
    printf("%d of elements\t\t%d times of comparisons.\n", length, counter);
  } else {
  printf("%d of elements\t%d times of comparisons.\n", length, counter);
  }
}
