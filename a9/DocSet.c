// Wen Xie, cs5007 assignment9, Mar 28
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

#include "DocSet.h"
#include "Hashtable.h"
#include "Util.h"

/*
// if has duplicate rowId, return 1
// this function will cause free invalid error, do not know why
int checkDuplicate(int rowId, LinkedList list) {
  LLIter iter = CreateLLIter(list);
  int* cur_node = NULL;
  LLIterGetPayload(iter, (void**)&cur_node);
  if (*cur_node == rowId) {
    //printf("==========row id is %d\n", *cur_node);
    //printf("duplicate33\n");
    DestroyLLIter(iter);
    //printf("line35\n");
    return 1;
  }
  while (LLIterHasNext(iter)) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&cur_node);
    if (*cur_node == rowId) {
      printf("duplicate41\n");
      DestroyLLIter(iter);
      return 1;
    }
  }
  DestroyLLIter(iter);
  return 0;
}
*/

int AddDocInfoToSet(DocumentSet set,  uint64_t docId, int rowId) {
  // STEP 4: Implement AddDocInfoToSet.
  // Make sure there are no duplicate rows or docIds.
  if (set == NULL) {
    return -1;
  }
  HTKeyValue kvp;
  HTKeyValue old_kvp;
  int* rowIdPtr = (int*)malloc(sizeof(int));
  *rowIdPtr = rowId;
  int result = LookupInHashtable(set->doc_index, docId, &kvp);
  if (result == 0) {  // this docId is in doc_index
    /*
    if (checkDuplicate(rowId, (LinkedList)kvp.value) == 1) {
      free(rowIdPtr);
      return -1;
    }
    */
    LLIter iter = CreateLLIter((LinkedList)kvp.value);
    int* cur_node = NULL;
    LLIterGetPayload(iter, (void**)&cur_node);
    if (*cur_node == rowId) {
      free(rowIdPtr);
      DestroyLLIter(iter);
      return -1;
    }
    while (LLIterHasNext(iter)) {
      LLIterNext(iter);
      LLIterGetPayload(iter, (void**)&cur_node);
      if (*cur_node == rowId) {
        free(rowIdPtr);
        DestroyLLIter(iter);
        return -1;
      }
    }
    // if no duplicate, add this rowId into the linkedlist
    InsertLinkedList((LinkedList)kvp.value, (void*)rowIdPtr);
    DestroyLLIter(iter);
    return 0;
  } else {  // this docId not yet in doc_index
    kvp.value = CreateLinkedList();
    kvp.key = docId;
    PutInHashtable(set->doc_index, kvp, &old_kvp);
    // no need to check duplicate
    InsertLinkedList((LinkedList)kvp.value, (void*)rowIdPtr);
    return 0;
  }
}

int DocumentSetContainsDoc(DocumentSet set, uint64_t docId) {
  // STEP 5: Implement DocumentSetContainsDoc
  HTKeyValue kvp;
  int result = LookupInHashtable(set->doc_index, docId, &kvp);
  return result;
}

void PrintOffsetList(LinkedList list) {
  printf("Printing offset list\n");
  LLIter iter = CreateLLIter(list);
  int* payload;
  while (LLIterHasNext(iter) != 0) {
    LLIterGetPayload(iter, (void**)&payload);
    printf("%d\t", *((int*)payload));
    LLIterNext(iter);
  }
}


DocumentSet CreateDocumentSet(char *desc) {
  DocumentSet set = (DocumentSet)malloc(sizeof(struct docSet));
  if (set == NULL) {
    // Out of memory
    printf("Couldn't malloc for movieSet %s\n", desc);
    return NULL;
  }
  int len = strlen(desc);
  set->desc = (char*)malloc((len + 1) *  sizeof(char));
  if (set->desc == NULL) {
    printf("Couldn't malloc for movieSet->desc");
    return NULL;
  }
  snprintf(set->desc, len + 1, "%s", desc);
  set->doc_index = CreateHashtable(16);
  return set;
}

/*
void DestroyNothing(void* payload) {
  return;
}
*/

void DestroyOffsetList(void *val) {
  LinkedList list = (LinkedList)val;
  DestroyLinkedList(list, &SimpleFree);
}

void DestroyDocumentSet(DocumentSet set) {
  // Free desc
  free(set->desc);
  // Free doc_index
  DestroyHashtable(set->doc_index, &DestroyOffsetList);
  // Free set
  free(set);
}
