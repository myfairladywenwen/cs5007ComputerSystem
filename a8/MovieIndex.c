// Wen Xie, CS5007 Assignment8, Mar 22, 2020
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "MovieIndex.h"
#include "htll/LinkedList.h"
#include "htll/Hashtable.h"
#include "Movie.h"
#include "MovieSet.h"

void DestroyMovieSetWrapper(void *movie_set) {
  DestroyMovieSet((MovieSet)movie_set);
}

void toLower(char *str, int len) {
  for (int i = 0; i < len; i++) {
    str[i] = tolower(str[i]);
  }
}

Index BuildMovieIndex(LinkedList movies, enum IndexField field_to_index) {
  Index movie_index = CreateIndex();

  // STEP 4(Student): Check that there is at least one movie
  // What happens if there is not at least one movie?
  if (NumElementsInLinkedList(movies) == 0) {
    return movie_index;
  }

  LLIter iter = CreateLLIter(movies);
  Movie* cur_movie;
  LLIterGetPayload(iter, (void**)&cur_movie);

  int result = AddMovieToIndex(movie_index, cur_movie, field_to_index);

  while (LLIterHasNext(iter)) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&cur_movie);
    result = AddMovieToIndex(movie_index, cur_movie, field_to_index);
  }
  DestroyLLIter(iter);
  return movie_index;
}


char* CheckAndAllocateString1(char* token) {
  char *out = (char *) malloc((strlen(token) + 1) * sizeof(char));
  snprintf(out, strlen(token) + 1, "%s", token);
  return out;
}


int AddMovieActorsToIndex(Index index, Movie *movie) {
  // STEP 6(Student): Add movies to the index via actors.
  //  Similar to STEP 5.
  /**
  for (int i = 0; i < movie->num_actors; i++) {
    toLower(movie->actor_list[i], sizeof(movie->actor_list[i]));
  }
  */

  int num_actors = movie->num_actors;
  for (int i = 0; i < num_actors; i++) {
    HTKeyValue kvp;
    HTKeyValue old_kvp;
    
    Movie* movieCopy = CreateMovie();
    movieCopy->title = CheckAndAllocateString1(movie->title);
    movieCopy->star_rating = movie->star_rating;
    movieCopy->content_rating = CheckAndAllocateString1(movie->content_rating);
    movieCopy->genre = CheckAndAllocateString1(movie->genre);
    movieCopy->duration = movie->duration;
    char** new_actor_list = (char**)malloc(sizeof(char*) * num_actors);
    movieCopy->actor_list = new_actor_list;
    for (int j = 0; j < movie->num_actors; j++) {
      movieCopy->actor_list[j] = CheckAndAllocateString1(movie->actor_list[j]);
    }
    movieCopy->num_actors = movie->num_actors;

    kvp.key = ComputeKey(movie, Actor, i);
    int result = LookupInHashtable(index, kvp.key, &old_kvp);

    if (result == 0) {  // exists
      MovieSet resultSet = old_kvp.value;
      if (checkDuplicate(movie, resultSet) == 1) {
        DestroyMovie(movieCopy);
        continue;
      }
      AddMovieToSet((MovieSet)old_kvp.value, movieCopy);
    } else if (result == -1) {
      MovieSet resultSet = CreateMovieSet(movie->actor_list[i]);
      HTKeyValue new_kvp;
      new_kvp.key = kvp.key;
      new_kvp.value = resultSet;
      PutInHashtable(index, new_kvp, &kvp);
      AddMovieToSet((MovieSet)new_kvp.value, movieCopy);
    }
  }
  return 0;
}

  // return 1 if has duplicate; return 0 if no duplicate
int checkDuplicate(Movie* movie, MovieSet movie_set) {
  LLIter iter = CreateLLIter(movie_set->movies);
  Movie* cur_movie;
  LLIterGetPayload(iter, (void**)&cur_movie);
  if (&cur_movie == movie) {
    DestroyLLIter(iter);
    return 1;
  }
  while (LLIterHasNext(iter)) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&cur_movie);
    if (&cur_movie == movie) {
      DestroyLLIter(iter);
      return 1;
    }
  }
  DestroyLLIter(iter);
  return 0;
}


int AddMovieToIndex(Index index, Movie *movie, enum IndexField field) {
  /**
  switch (field) {
    case Genre:
      toLower(movie->genre, sizeof(movie->genre));
      break;
    case ContentRating:
      toLower(movie->content_rating, sizeof(movie->content_rating));
      break;
    default:
      break;
  }
  */

  // toLower(movie->content_rating, sizeof(movie->content_rating));

  if (field == Actor) {
    return AddMovieActorsToIndex(index, movie);
  }

  HTKeyValue kvp;
  kvp.key = ComputeKey(movie, field, 0);
  // STEP 5(Student): How do we add movies to the index?
  // The general idea:
  // Check hashtable to see if relevant MovieSet already exists
  // If it does, grab access to it from the hashtable
  // If it doesn't, create the new MovieSet and get the pointer to it
  // Put the new MovieSet into the Hashtable.

  // After we either created or retrieved the MovieSet from the Hashtable:
  int result = LookupInHashtable(index, kvp.key, &kvp);
  if (result == 0) {  // exists
    MovieSet resultSet = kvp.value;
    if (checkDuplicate(movie, resultSet) == 1) {
        return 0;
    }
    AddMovieToSet((MovieSet)kvp.value, movie);
  } else if (result == -1) {  // not yet there
    char* desc;
    switch (field) {
      case Genre:
        desc = movie->genre;
        break;
      case StarRating:
        desc = (char*)malloc(sizeof(char) * 10);
        sprintf(desc, "%f", movie->star_rating);
        break;
      case ContentRating:
        desc = movie->content_rating;
        break;
      default:
        return -1;
    }
    MovieSet resultSet = CreateMovieSet(desc);
    if (resultSet == NULL) {
      return -1;
    }
    HTKeyValue new_kvp;
    new_kvp.key = kvp.key;
    new_kvp.value = (void*)resultSet;
    PutInHashtable(index, new_kvp, &kvp);
    AddMovieToSet((MovieSet)new_kvp.value, movie);
  }
  return 0;
}


uint64_t ComputeKey(Movie* movie,
                    enum IndexField which_field, int which_actor) {
  char rating_str[10];
  switch (which_field) {
    case Genre:
      return FNVHash64((unsigned char*)movie->genre, strlen(movie->genre));
    case StarRating:
      snprintf(rating_str, 10, "%f", movie->star_rating);
      return FNVHash64((unsigned char*)rating_str, strlen(rating_str));
    case ContentRating:
      return FNVHash64((unsigned char*)movie->content_rating,
                       strlen(movie->content_rating));
    case Actor:
      if (which_actor < movie->num_actors) {
        return FNVHash64((unsigned char*)movie->actor_list[which_actor],
                         strlen(movie->actor_list[which_actor]));
      }
      break;
  }
  return -1u;
}

// Removed for simplicity
// MovieSet GetMovieSet(Inex index, const char *term){}

int DestroyIndex(Index index) {
  DestroyHashtable(index, &DestroyMovieSetWrapper);
  return 0;
}

Index CreateIndex() {
  return CreateHashtable(128);
}
