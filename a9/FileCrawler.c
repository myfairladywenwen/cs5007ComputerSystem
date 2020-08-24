// Wen Xie, cs5007 assignment9, Mar28
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
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#include "FileCrawler.h"
#include "DocIdMap.h"
#include "LinkedList.h"


/**
 * Iterates through a given directory, and for all files it
 * finds, adds them to the provided DocIdMap to assign a unique
 * id.
 *
 * The result of this function is a DocIdMap that contains all the files
 * we will want to index and search.
 *
 * \param dir which directory to crawl
 * \param map the DocIdMap to put the filenames in.
 */
void CrawlFilesToMap(const char *dir, DocIdMap map) {
  // STEP 3: Implement the file crawler.
  // Use namelist (declared below) to find files and put in map.
  // NOTE: There may be nested folders.
  // Be sure to lookup how scandir works. Don't forget about memory use.

  struct stat s;

  struct dirent **namelist;
  // point to an allocated array of pointers to
  // allocated strings each of which points to
  // an allocated block containing the null-terminated name of a file.

  if (stat(dir, &s) != 0) {
  return;
  }
  if (!S_ISDIR(s.st_mode)) {
    return;
  }

  int n;  // num of dir entries in path dir
  n = scandir(dir, &namelist, 0, alphasort);

  struct dirent* name = NULL;
  for (int i = 0; i < n; i++) {
    name = namelist[i];  // current file or directory
    if (strcmp(name->d_name, ".") == 0 || strcmp(name->d_name, "..") == 0) {
      free(name);
      name = NULL;
      continue;
    }
    char* path = (char*)malloc(sizeof(char) * 100);
    strcpy(path, dir);
    if (dir[strlen(dir)-1] != '/') {
      strcat(path, "/");  // manually add / to the directory name
    }
    strcat(path, name->d_name);
    if (name->d_type == DT_REG) {
      PutFileInMap(path, map);
      // printf("%s\n", path);
    } else if (name->d_type == DT_DIR) {
      strcat(path, "/");
      CrawlFilesToMap(path, map);
      free(path);
    }
    free(name);
  }
  free(namelist);
}


// DO need to free the memory returned to you by scandir().

/*
for (int i = 0; i < n; i++) {
  free(namelist[i];
}
free(namelist);
*/
