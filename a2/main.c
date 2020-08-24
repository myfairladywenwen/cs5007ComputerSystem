#include <stdio.h>
#include "sort.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

void PrintArray(int length, const int* a);
int main() {
  int const KMIN = 0;
  int const KMAX = 1000;
  // value of the array elements would be in range from 0 to 999
  int const KTIMES = 10;  // for each level(large/medium/small), try 10 times
  printf("----------\nSORTING:\n----------\n");

  int* times_arr_small = (int*)malloc(sizeof(KMIN) * KTIMES);
  for (int i = 0; i < KTIMES; i++) {
    times_arr_small[i] = (int)pow(2, i);
  // the array sizes would be 0,2,4,8,16,32,64,128,256,512
  }
  for (int t = 0; t < KTIMES; t++) {
    int length = times_arr_small[t];
    int* arr = (int*)malloc(sizeof(KMIN) * length);
    srandom(time(0));
    // generate elements for each array
    for (int i = 0; i< length; i++) {
      arr[i] = KMIN + (rand()%KMAX);
    }
    printf("Small:\t");
    Sort(arr, length);
    free(arr);
  }
  free(times_arr_small);

  int* times_arr_med = (int*)malloc(sizeof(KMIN) * 10);
  for (int i = 0; i < KTIMES; i++) {
    times_arr_med[i]= (int)pow(2, 10+i);
  }
  for (int t = 0; t < KTIMES; t++) {
    int length = times_arr_med[t];
    int* arr = (int*)malloc(sizeof(KMIN) * length);
    srandom(time(0));
    for (int i = 0; i< length; i++) {
      arr[i] = KMIN + (rand()%KMAX);
    }
    printf("Med:\t");
    Sort(arr, length);
    free(arr);
  }
  free(times_arr_med);

  int* times_arr_large = (int*)malloc(sizeof(KMIN) * KTIMES);
  for (int i = 0; i < KTIMES; i++) {
    times_arr_large[i] = (int)pow(2, 20+i);
    // the array sizes would be 2^10,2^11,2^12,...2^19
  }
  for (int t = 0; t < KTIMES; t++) {
    int length = times_arr_large[t];
    int* arr = (int*)malloc(sizeof(KMIN) * length);
    srandom(time(0));
    // generate elements for each array
    for (int i = 0; i< length; i++) {
      arr[i] = KMIN + (rand());
    }
    printf("Large:\t");
    Sort(arr, length);
    free(arr);
  }
  free(times_arr_large);
return 0;
}

void PrintArray(int length, const int* a) {
  for (int i = 0; i < length; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
