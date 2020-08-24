#include <stdio.h>
int main(){
  printf("%s\n", "method1:");
  printf("%s", "VICTORY\nVICTORY\nVICTORY\n");
  printf("%s\n", "method2:");
  printf("%s\n", "VICTORY");
  printf("%s\n", "VICTORY");
  printf("%s\n", "VICTORY");
  printf("%s\n", "method3:");
  for (int i = 0; i < 3; i++){
    printf("%s\n","VICTORY");
  }
  return 0;
}
