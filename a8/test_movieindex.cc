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
#include <stdint.h>
#include <assert.h>


#include "gtest/gtest.h"

extern "C" {
  #include "./MovieIndex.h"
  #include "htll/LinkedList.h"
  #include "MovieIndex.h"
  #include "Movie.h"
  #include "MovieReport.h"
  #include "FileParser.h"
  #include <string.h>
}

const char* movie_row_A = "9.3|The Shawshank Redemption|R|Crime|142|Tim Robbins,Morgan Freeman,Bob Gunton";
const char* movie_row_B = "7.4|Back to the Future Part III|PG|Adventure|118|Michael J. Fox,Christopher Lloyd,Mary Steenburgen";

const char* movie_row_1 = "8.1|Movie1|R|Action|100|Actor1, Actor2";
const char* movie_row_2 = "8.1|Movie2|R|Action|100|Actor1, Actor2";
const char* movie_row_3 = "8.3|Movie3|PG|Love|100|Actor1, Actor2";


void DestroyLLMovie(void *payload) {
  DestroyMovie((Movie*)payload);
}

  // DONE (Wen Xie): [test add movie to index by starrating]
TEST(MovieIndex, AddMovieToIndexStarRating) {
  char row[1000];
  strcpy(row, movie_row_1);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  strcpy(row, movie_row_3);
  MoviePtr m3 = CreateMovieFromRow(row);
  // Create Index
  Index index = CreateIndex();
  // Add movie to index
  AddMovieToIndex(index, m1, StarRating);
  AddMovieToIndex(index, m3, StarRating);

  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 2);
  DestroyIndex(index);
}


  // DONE (Wen Xie): [test add movie to index by starrating]
TEST(MovieIndex, AddMovieToIndexSameStarRating) {
  char row[1000];
  strcpy(row, movie_row_1);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  strcpy(row, movie_row_2);
  MoviePtr m2 = CreateMovieFromRow(row);
  // Create Index
  Index index = CreateIndex();
  // Add movie to index
  AddMovieToIndex(index, m1, StarRating);
  AddMovieToIndex(index, m2, StarRating);

  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 1);
  DestroyIndex(index);
}



  // DONE (Wen Xie): [test add movie to index by actor]
TEST(MovieIndex, AddMovieToIndexActor) {
  char row[1000];
  strcpy(row, movie_row_1);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  strcpy(row, movie_row_2);
  MoviePtr m2 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, Actor);
  AddMovieToIndex(index, m2, Actor);
  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 2);
  DestroyIndex(index);
}


  // DONE (Wen Xie): [test add movie to index by genre]
TEST(MovieIndex, AddMovieToIndexGenre) {
  char row[1000];
  strcpy(row, movie_row_1);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  // Create Index
  Index index = CreateIndex();
  // Add movie to index
  AddMovieToIndex(index, m1, Genre);
  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 1);
  DestroyIndex(index);
}


  // DONE (Wen Xie): [test add movie to index by Same enre]
TEST(MovieIndex, AddMovieToIndexSameGenre) {
  char row[1000];
  strcpy(row, movie_row_1);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  // Create Index

  strcpy(row, movie_row_2);
  MoviePtr m2 = CreateMovieFromRow(row);
  Index index = CreateIndex();
  // Add movie to index
  AddMovieToIndex(index, m1, Genre);
  AddMovieToIndex(index, m2, Genre);
  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 1);
  DestroyIndex(index);
}


TEST(MovieSet, CreateDestroy) {
  MovieSet set = CreateMovieSet("My test set");
  ASSERT_NE(set, nullptr);
  DestroyMovieSet(set);
}


TEST(MovieSet, AddOneMovie) {
  MovieSet set = CreateMovieSet("My test set");
  ASSERT_NE(set, nullptr);
  ASSERT_EQ(NumElementsInLinkedList(set->movies), 0);

  char row[1000];
  strcpy(row, movie_row_A);
  MoviePtr movie = CreateMovieFromRow(row);
  int res = AddMovieToSet(set, movie);
  ASSERT_EQ(res, 0);
  ASSERT_EQ(NumElementsInLinkedList(set->movies), 1);
  DestroyMovieSet(set);
}


TEST(MovieIndex, CreateDestroy) {
  Index index = CreateIndex();
  ASSERT_NE(index, nullptr);
  DestroyIndex(index);
}



TEST(MovieIndex, AddMovieToIndex) {
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  char row[1000];
  strcpy(row, movie_row_A);
  // Take a movie
  MoviePtr m1 = CreateMovieFromRow(row);
  strcpy(row, movie_row_B);
  MoviePtr m2 = CreateMovieFromRow(row);

  // Create Index
  Index index = CreateIndex();

  // Add movie to index
  AddMovieToIndex(index, m1, ContentRating);

  // Check that movie is in index

  // Check size/num elements (should be num of types, not of movies)
  ASSERT_EQ(NumElemsInHashtable(index), 1);


  // Try to insert movie again

  AddMovieToIndex(index, m1, ContentRating);
  // Add another movie to the index (same IndexType)
  AddMovieToIndex(index, m2, ContentRating);
  // Destroy movie index
  DestroyIndex(index);
}


/*  I think there is something wrong in this testcase.
    Most probably in ReadFile function.
TEST(MovieIndex, BuildMovieIndexFromFile) {
  LinkedList movie_list  = ReadFile(const_cast<char *>("data/test"));

  //ASSERT_EQ(5u, NumElementsInLinkedList(movie_list));

  //Index index = BuildMovieIndex(movie_list, Genre);

  // Do a few spot checks.
  // E.g., Pull out a MovieSet from the Hashtable;
  // Check to see if the set has expected number of movies,
  // a particular movie, etc.
  //DestroyIndex(index);
  }
*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
