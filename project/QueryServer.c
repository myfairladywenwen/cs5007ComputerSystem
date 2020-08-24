// Wen Xie, cs5007 fianl project, Apr 9
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#include "DirectoryParser_MT.h"
#include "QueryProtocol.h"
#include "MovieSet.h"
#include "MovieIndex.h"
#include "MovieTitleIndex.h"
#include "DocIdMap.h"
#include "Hashtable.h"
#include "QueryProcessor.h"
#include "FileParser.h"
#include "FileCrawler.h"
#include "DirectoryParser.h"
#include "Util.h"

DocIdMap docs;
MovieTitleIndex docIndex;

#define BUFFER_SIZE 1000
#define kMaxRowLength 1000

#define SEARCH_RESULT_LENGTH 1500
char movieSearchResult[SEARCH_RESULT_LENGTH];

int Cleanup();

int CreateMovieFromFileRow(char *file, long row_id, Movie** movie) {
  FILE *cfPtr;
  if ((cfPtr = fopen(file, "r")) == NULL) {
    printf("File could not be opened\n");
    return -1;
  } else {
    // Assert007(cfPtr != NULL);
    char row[kMaxRowLength];
    int i = 0;
    while (i < row_id) {
      char* res = fgets(row, kMaxRowLength, cfPtr);
      if (res == NULL) break;
      i++;
    }
    char* res = fgets(row, kMaxRowLength, cfPtr);
    // Got the line; create a movie from it
    *movie = CreateMovieFromRow(row);
    // Assert007(movie != NULL);
    fclose(cfPtr);
    return 0;
  }
}


char* read_response(int client_fd) {
  // Response
  char* resp = (char*)malloc(sizeof(char)*SEARCH_RESULT_LENGTH);
  int len = read(client_fd, resp, SEARCH_RESULT_LENGTH - 1);
  resp[len] = '\0';
  printf("server RECEIVED: %s\n", resp);
  return resp;
}



void sigint_handler(int sig) {
  write(0, "Exit signal sent. Cleaning up...\n", 34);
  Cleanup();
  exit(0);
}

int HandleClient(int sock_fd) {
  // Step 5: Accept connection

  printf("Waiting for connection...\n");
  int client_fd = accept(sock_fd, NULL, NULL);
  printf("Connection made: client_fd=%d\n", client_fd);

  // Step 6: Read, then write if you want
  int sendACK = SendAck(client_fd);
  if (sendACK != 0) {
    return -1;
  }

  char query[BUFFER_SIZE];
  int len = read(client_fd, query, BUFFER_SIZE - 1);
  query[len] = '\0';
  printf("SERVER RECEIVED: %s \n", query);

  // Listen for query
  // If query is GOODBYE close ocnnection
  if (CheckGoodbye(query) == 0) {
    close(client_fd);
    return -1;
  }

  // Run query and get responses
  printf("returning movieset\n");
  SearchResultIter iter = FindMovies(docIndex, query);
  int resultCount;
  if (iter == NULL) {
    resultCount = 0;
  }
  // Send number of responses
  // printf("Getting docs for movieset term: \" %s \"", query);
  resultCount = NumResultsInIter(iter);
  write(client_fd, &resultCount, sizeof(int));

  // Wait for ACK
  char* response = read_response(client_fd);
  if (CheckAck(response) != 0) {
    free(response);
    close(client_fd);
    return -1;
  }
  if (resultCount == 0) {
    SendGoodbye(client_fd);
    free(response);
    close(client_fd);
    return -1;
  }
  // For each response
    // Send response
    // Wait for ACK
  free(response);

  SearchResult sr = (SearchResult)malloc(sizeof(*sr));
  if (sr == NULL) {
    printf("Couldn't malloc SearchResult in main.c\n");
    return -1;
  }
  int result;
  char *filename;

  // Check if there are more
  while (SearchResultIterHasMore(iter) != 0) {
    SearchResultGet(iter, sr);
    char* movieinfo = (char*)malloc(sizeof(char)*SEARCH_RESULT_LENGTH);
    CopyRowFromFile(sr, docs, movieinfo);
    write(client_fd, movieinfo, strlen(movieinfo));
    response = read_response(client_fd);
    CheckAck(response);
    free(response);
    free(movieinfo);
    SearchResultNext(iter);
  }  // end-while
  // deal with last one
  SearchResultGet(iter, sr);
  char* movieinfo = (char*)malloc(sizeof(char)*1500);
  CopyRowFromFile(sr, docs, movieinfo);
  write(client_fd, movieinfo, strlen(movieinfo));
  free(movieinfo);
  response = read_response(client_fd);
  CheckAck(response);
  free(response);

  free(sr);
  DestroySearchResultIter(iter);

  SendGoodbye(client_fd);
  // close connection.
  close(client_fd);
  return 0;
}



int Setup(char *dir) {
  printf("Crawling directory tree starting at: %s\n", dir);
  // Create a DocIdMap
  docs = CreateDocIdMap();
  CrawlFilesToMap(dir, docs);
  printf("Crawled %d files.\n", NumElemsInHashtable(docs));

  // Create the index
  docIndex = CreateMovieTitleIndex();

  if (NumDocsInMap(docs) < 1) {
    printf("No documents found.\n");
    return 0;
  }

  // Index the files
  printf("Parsing and indexing files...\n");
  ParseTheFiles(docs, docIndex);
  printf("%d entries in the index.\n", NumElemsInHashtable(docIndex->ht));
  return NumElemsInHashtable(docIndex->ht);
}

int Cleanup() {
  DestroyMovieTitleIndex(docIndex);
  DestroyDocIdMap(docs);
  return 0;
}

int main(int argc, char **argv) {
  char *port = NULL;
  char *dir_to_crawl = NULL;

  int debug_flag = 0;
  int c;

  while ((c = getopt (argc, argv, "dp:f:")) != -1) {
    switch (c) {
      case 'd':
        debug_flag = 1;
        break;
      case 'p':
        port = optarg;
        break;
      case 'f':
        dir_to_crawl = optarg;
        break;
      }
  }

  if (port == NULL) {
    printf("No port provided; please include with a -p flag.\n");
    exit(0);
  }

  if (dir_to_crawl == NULL) {
    printf("No directory provided; please include with a -f flag.\n");
    exit(0);
  }

  // Setup graceful exit
  struct sigaction kill;

  kill.sa_handler = sigint_handler;
  kill.sa_flags = 0;  // or SA_RESTART
  sigemptyset(&kill.sa_mask);

  if (sigaction(SIGINT, &kill, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  int num_entries = Setup(dir_to_crawl);
  if (num_entries == 0) {
    printf("No entries in index. Quitting. \n");
    exit(0);
  }

  int s;
  // Step 1: Get address stuff
  // struct addrinfo hints, *result;

  // Setting up the hints struct...
  // memset(&hints, 0, sizeof(struct addrinfo));
  // hints.ai_family = AF_INET;
  // hints.ai_socktype = SOCK_STREAM;
  // hints.ai_flags = AI_PASSIVE;

  // s = getaddrinfo("localhost", "1500", &hints, &result);
  // if (s != 0) {
  // fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
  // return 1;
  // }

  struct sockaddr_in serv;
  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = htonl(INADDR_ANY);
  serv.sin_port = htons(atoi(port));

  // Step 2: Open socket
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  // Step 3: Bind socket
  // if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
  // perror("bind()");
  // return 1;
  // }

  if (bind(sock_fd, (struct sockaddr*)&serv, sizeof(struct sockaddr)) != 0) {
    perror("bind()");
    return 1;
  }
  // Step 4: Listen on the socket
  if (listen(sock_fd, 10) != 0) {
    perror("listen()");
    return 1;
  }
  // struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr;
  // printf("Listening on file descriptor %d, port %d\n", sock_fd, ntohs(result_addr->sin_port));

  while (1) {
    HandleClient(sock_fd);
  }
  // Got Kill signal
  close(sock_fd);

  Cleanup();

  return 0;
}
