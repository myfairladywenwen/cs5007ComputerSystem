// Wen Xie, CS5007 Assignment8, Mar22, 2020
/*
 *  Adrienne Slaughter
 *  5007 Spr 2020
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <ctype.h>
#include <unistd.h>


#include "htll/LinkedList.h"
#include "MovieIndex.h"
#include "Movie.h"
#include "MovieReport.h"
#include "./FileParser.h"

void DestroyNothing(void* thing) {
  // Helper method to destroy the LinkedList.
}

int main(int argc, char* argv[]) {
  // STEP 8(Student): Check args, do the right thing.
  int ch;
  opterr = "invalid flag\n";
  enum IndexField field_to_index;

  if (argc != 3) {
    printf("invalid number of arguments.\n");
    return -1;
  }
  while((ch = getopt(argc, argv, "-s-c-g-a")) != -1){
   switch(argv[1][1]) {
      case 's':
         field_to_index = StarRating;
         break;
      case 'c':
        field_to_index = ContentRating;
        break;
      case 'g':
        field_to_index = Genre;
        break;
     case 'a':
        field_to_index = Actor;
        break;
     default:
       //printf("not a valid flag: %s\n", argv[1]);
         return -1;
   }
  }

  /**
   switch(argv[1][1]) {
      case 's':
         field_to_index = StarRating;
         break;
      case 'c':
        field_to_index = ContentRating;
        break;
      case 'g':
        field_to_index = Genre;
        break;
     case 'a':
        field_to_index = Actor;
        break;
     default:
         printf("not a valid flag: %s\n", argv[1]);
         break;
     }
  */
  
  char* filename = argv[2]; 
  LinkedList movie_list  = ReadFile(filename);
  Index index; // STEP 9(Student): Create the index properly. 
  index  = BuildMovieIndex(movie_list, field_to_index);
  PrintReport(index);
  DestroyLinkedList(movie_list, &DestroyMovie);
  DestroyIndex(index);

  return 0;
}
