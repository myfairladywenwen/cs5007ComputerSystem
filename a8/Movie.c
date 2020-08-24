  // Wen Xie, CS5007 assignment 8, Mar 22, 2020

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
#include <string.h>

#include "Movie.h"


Movie* CreateMovie() {
  Movie *mov = (Movie*)malloc(sizeof(Movie));
  if (mov == NULL) {
    printf("Couldn't allocate more memory to create a Movie\n");
    return NULL;
  }

  mov->title = NULL;
  mov->star_rating = 0;
  mov->content_rating = NULL;
  mov->genre = NULL;
  mov->duration = 0;
  mov->actor_list = NULL;
  mov->num_actors = 0;

  return mov;
}

void DestroyMovie(Movie* movie) {
  // STEP 1(Student): Make sure the movie is destroyed properly.
  if (movie == NULL) {
    return;
  }
  if (movie->title != NULL) {
    free(movie->title);
  }
  if (movie->content_rating != NULL) {
    free(movie->content_rating);
  }
  if (movie->genre != NULL) {
    free(movie->genre);
  }
  if (movie->actor_list != NULL) {
    for (int i = 0; i < movie->num_actors; i++) {
      if (movie->actor_list[i] != NULL) {
        free(movie->actor_list[i]);
      }
    }
    free(movie->actor_list);
  }
  free(movie);
}
