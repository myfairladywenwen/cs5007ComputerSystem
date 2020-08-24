/*
  a3.c created by Wen Xie
  on Jan 25
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "a3.h"

// YOUR CODE GOES HERE
void Big(Name* name) {
  printf("%s ", name->first);
  if (name->middle) {
    printf("%s ", name->middle);
  }
  printf("%s ", name->last);
}

void Last(Name *name) {
  printf("%s, ", name->last);
  printf("%s", name->first);
}

// Print the string <first> <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben Bitdiddle".
//
// name: a pointer to a Name
void Reg(Name *name) {
  printf("%s ", name->first);
  printf("%s", name->last);
}

// Print the string <first> <middle-initial>. <last>
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben I. Bitdiddle".
//
// If middle name is NULL, print:
// "Ben Bitdiddle"
//
// name: a pointer to a Name
void Mid(Name *name) {
  printf("%s ", name->first);
  if (name->middle) {
    printf("%c. ", name->middle[0]);
  }
  printf("%s", name->last);
}

// Print the first name only.
//  e.g. if first = "Ben", middle = "Ivan",
//  and last = "Bitdiddle, then print:
//  "Ben".
//
// name: a pointer to a Name
void Small(Name *name) {
  printf("%s", name->first);
}

// Given a format char, print the given
// name in the format specified by char.
// The mapping is shown below:
// B -> 'big' format
// L -> 'last' format
// R -> 'reg' format
// M -> 'mid' format
// S -> 'small' format
//
// name: a pointer to a Name
// format: a char indicating the format to use (case doesn't matter)
void FormatName(Name *name, char format) {
  if (format == 'B' || format =='b') {
    Big(name);
  } else if (format == 'L' || format == 'l') {
    Last(name);
  } else if (format == 'R' || format == 'r') {
    Reg(name);
  } else if (format == 'M' || format == 'm') {
    Mid(name);
  } else if (format == 'S' || format == 's') {
    Small(name);
  }
}

// Given a name, a format and a destination array,
// put the properly formatted name in the destination
// array, not printing anything on the screen.
//
// The mapping is shown below:
// B -> 'big' format
// L -> 'last' format
// R -> 'reg' format
// M -> 'mid' format
// S -> 'small' format
//
// name: a pointer to a Name
// format: a char indicating the format to use (case doesn't matter)
// dest: a pointer to an array that is guaranteed to be big enough
// to hold the formatted name
void FillName(Name *name, char format, char *dest) {
  int len;
  if (format == 'B' || format =='b') {
    if (name->middle) {
      snprintf(dest, strlen(name->first) + strlen(name->middle) +\
               strlen(name->last) + 3, "%s %s %s", \
               name->first, name->middle, name->last);
          } else {
      snprintf(dest, strlen(name->first) + strlen(name->last) + 2,
               "%s %s", name->first, name->last);
    }
  } else if (format == 'L' || format == 'l') {
    snprintf(dest, strlen(name->last) + strlen(name->first)+ 3, \
             "%s, %s", name->last, name->first);
  } else if (format == 'R' || format == 'r') {
    snprintf(dest, strlen(name->last) + strlen(name->first)+ 2, \
             "%s %s", name->first, name->last);
  } else if (format == 'M' || format == 'm') {
    if (name->middle) {
      snprintf(dest, strlen(name->first) + strlen(name->last) + 5, \
               "%s %c. %s", name->first, name->middle[0], name->last);
    } else {
      snprintf(dest, strlen(name->first) + strlen(name->last) + 2, \
               "%s %s", name->first, name->last);
    }
  } else if (format == 'S' || format == 's') {
    snprintf(dest, strlen(name->first) + 1, "%s", name->first);
  }
}

