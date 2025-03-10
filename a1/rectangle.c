#include <stdio.h>
const int EDGE = 2;

int main(){
  PrintRectangle(5, 4);
  PrintFancyRectangle(5, 4, '+', 0);
  PrintFancyRectangle(5, 4, '*', 1);
  return 0;
}

/*
 * This function prints an empty rectangle of the specified width and height.
 */
void PrintRectangle(int width, int height){
  const char* SYMBOL = "-";
  for(int i = 0; i < width; i++){
    printf("%s", SYMBOL);
  }
  printf("\n");
  for(int i = 0; i < height - EDGE; i++ ){
    printf("%s", SYMBOL);
    for(int i = 0; i < width - EDGE; i++){
      printf(" ");
    }
    printf("%s\n",SYMBOL);
  }
  for(int i = 0; i < width; i++){
    printf("%s", SYMBOL);
  }
  printf("\n");
}

/*
 * This is a function prints a fancy rectangle.
 */
void PrintFancyRectangle(int width, int height, char symbol, int fill){
  const int KFill = 1;
  const int KUnfill = 0;
  for(int i = 0; i < width; i++){
    printf("%c", symbol);
  }
  printf("\n");

  for(int i = 0; i < height - EDGE; i++ ){
    printf("%c", symbol);
    if (fill == KUnfill){
      for(int i = 0; i < width - EDGE; i++){
        printf(" ");
      }
    }
    else {
      for(int i = 0; i < width - EDGE; i++){
        printf("%c", symbol);
      }
    }
    printf("%c\n",symbol);
  }
  for(int i = 0; i < width; i++){
    printf("%c", symbol);
  }
  printf("\n");
}
