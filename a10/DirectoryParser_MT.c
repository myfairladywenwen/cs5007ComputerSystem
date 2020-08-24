
// Wen Xie, cs5007 assignment10, Apr 1
/*
 *  Created by Adrienne Slaughter
 *  CS 5007 Summer 2019
 *  Northeastern University, Seattle
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#include "DirectoryParser.h"
#include "MovieTitleIndex.h"
#include "Movie.h"
#include "DocIdMap.h"


#define BUFFER_SIZE 1000

//=======================
// To minimize the number of files we have, I'm
// putting the private function prototypes for
// the DirectoryParser here.

/**
 * Helper function to index a single file.
 *
 * \return a pointer to the number of records (lines) indexed from the file
 */
void* IndexAFile_MT(void *toBeIter);


pthread_mutex_t ITER_MUTEX = PTHREAD_MUTEX_INITIALIZER;  // global variable
pthread_mutex_t INDEX_MUTEX = PTHREAD_MUTEX_INITIALIZER;  // global variable

// THINK: Why is this global?
// Because all threads need to get access to same movieIndex
MovieTitleIndex movieIndex;
// HTIter iter;

int ParseTheFiles_MT(DocIdMap docs, MovieTitleIndex index, int num_threads) {
  // Create the iterator
  // Create the threads
  // Spawn the threads to work on the function IndexTheFile_MT

  clock_t start, end;
  double cpu_time_used;
  start = clock();
  movieIndex = index;

  // count how many files we have
  int file_count = NumElemsInHashtable(docs);
  printf("file count =  %d\n", file_count);

  HTIter iter = CreateHashtableIterator(docs);
  printf("use %d threads.\n", num_threads);

  int file_processed = 0;
  while (file_processed < file_count) {
    pthread_t thread_id[num_threads];
    for (int i = 0; i < num_threads; i++) {
      pthread_create(&thread_id[i], NULL, IndexAFile_MT, &iter);
      // printf("thread %d created\n", i);
    }
    for (int i = 0; i < num_threads; i++) {
      pthread_join(thread_id[i], NULL);
      // printf("thread %d joined\n", i);
    }
    file_processed += num_threads;
  }
  printf("use %d threads.\n", num_threads);

  DestroyHashtableIterator(iter);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("Took %f seconds to execute. \n", cpu_time_used);
  return 0;
}

void* IndexAFile_MT(void *docname_iter) {
  // Lock the iterator
  // Get the filename, unlock the iterator
  // Read the file
  // Create movie from row
  // Lock the index
  // Add movie to index
  // Unlock the index
  HTIter iter = *((HTIter*)(docname_iter));
  // Don't forget to free this at some point!!
  int* num_records = (int*)malloc(sizeof(int));
  *num_records = 0;

  if (iter == NULL) {
    return;
  }

  // lock the iter
  pthread_mutex_lock(&ITER_MUTEX);
  // printf("iter locked %p\n", &iter);

  // get the filename
  HTKeyValue curr;
  int result = HTIteratorGet(iter, &curr);
  // curr.key is unique ID, curr.value is filename
  if (HTIteratorHasMore(iter)) {
    HTIteratorNext(iter);
  }
  pthread_mutex_unlock(&ITER_MUTEX);


  FILE *cfPtr;
  if ((cfPtr = fopen(curr.value, "r")) == NULL) {
    printf("File could not be opened\n");
    return 0;
  } else {
    char buffer[BUFFER_SIZE];
    // int row = 0;
    while (fgets(buffer, BUFFER_SIZE, cfPtr) != NULL) {
      Movie *movie = CreateMovieFromRow(buffer);
      // lock the index
      pthread_mutex_lock(&INDEX_MUTEX);
      // printf("index locked\n");
      // add movie to index
      int result = AddMovieTitleToIndex(movieIndex, movie, curr.key, *num_records);
      if (result < 0) {
        fprintf(stderr, "Didn't add MovieToIndex.\n");
      }

      // unlock the index
      pthread_mutex_unlock(&INDEX_MUTEX);
      // printf("index unlocked\n");
      (*num_records)++;
      // row++;
      DestroyMovie(movie);  // Done with this now
    }
    fclose(cfPtr);
  }
  free(num_records);
  // return (void*)num_records;
  return 0;
}
