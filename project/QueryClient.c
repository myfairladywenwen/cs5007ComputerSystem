// Wen Xie, cs5007 final project, Apr 9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#include "QueryProtocol.h"

char *port_string = "1500";  // dest(server)
unsigned short int port;
char *ip = "127.0.0.1";  // dest(server)

#define BUFFER_SIZE 1000


char* read_response(int sock_fd) {
  // Response
  char* resp = (char*)malloc(sizeof(char) * BUFFER_SIZE);
  int len = read(sock_fd, resp, BUFFER_SIZE - 1);
  resp[len] = '\0';
  return resp;
}

void read_count(int sock_fd, int* count) {
  read(sock_fd, count, sizeof(int));
}


void RunQuery(char *query) {
  // Find the address

  // Create the socket

  // Connect to the server

  int s;
  struct addrinfo hints, *result;

  // Allows "global"
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;  /* IPv4 only */
  hints.ai_socktype = SOCK_STREAM;  /* TCP */

  s = getaddrinfo(ip, port_string, &hints, &result);
  // If I can't get the address, write an error.
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    return;
  }

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  // try to connect; return 1 if connect, 0 if cannot
  connect(sock_fd, result->ai_addr, result->ai_addrlen);
  printf("Connection is good!\n");
  freeaddrinfo(result);
  // listen for an ack
  char* response = read_response(sock_fd);  // should be ack
  assert(CheckAck(response) == 0);
  free(response);

  write(sock_fd, query, strlen(query));
    // Do the query-protocol
    // check client input is Goodbye
    // if (CheckGoodbye(query) == 0) {
    // close(sock_fd);
    // return;
    // }
  int count;
  read_count(sock_fd, &count);
  SendAck(sock_fd);
  for (int i = 0; i < count; i++) {
    char* movie = read_response(sock_fd);
    printf("%s\n", movie);
    free(movie);
    SendAck(sock_fd);
  }

  char* goodbye = read_response(sock_fd);
  assert(CheckGoodbye(goodbye) == 0);
  free(goodbye);
    // Close the connection
  close(sock_fd);
  return;
}

void RunPrompt() {
  char input[BUFFER_SIZE];
  while (1) {
    printf("Enter a term to search for, or q to quit: ");
    scanf("%s", input);

    printf("input was: %s\n", input);

    if (strlen(input) == 1) {
      if (input[0] == 'q') {
        printf("Thanks for playing! \n");
        return;
      }
    }
    printf("\n\n");
    RunQuery(input);
  }
}

  // This function connects to the given IP/port to ensure
  // that it is up and running, before accepting queries from users.
  // Returns 0 if can't connect; 1 if can.
int CheckIpAddress(char *ip, char *port) {
  // Connect to the server
  // Listen for an ACK
  // Send a goodbye
  // Close the connection
  int s;
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct addrinfo hints, *result;

  // Allows "global"
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;  /* IPv4 only */
  hints.ai_socktype = SOCK_STREAM;  /* TCP */

  s = getaddrinfo(ip, port, &hints, &result);
  // If I can't get the address, write an error.
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    freeaddrinfo(result);
    return 0;
  }

  // try to connect; return 1 if connect, 0 if cannot
  if (connect(sock_fd, result->ai_addr, result->ai_addrlen) == -1) {
     perror("connect");
     freeaddrinfo(result);
     return 0;
  } else {
    printf("Connection is good!\n");
    // listen for an ack
    printf("listen for ack\n");
    char* response = read_response(sock_fd);
    if (CheckAck(response) == 0) {
      if (SendGoodbye(sock_fd)== 0) {
        free(response);
        close(sock_fd);
        freeaddrinfo(result);
        return 1;
      }
    }
    freeaddrinfo(result);
    return 1;
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Incorrect number of arguments. \n");
    printf("Correct usage: ./queryclient [IP] [port]\n");
  } else {
    ip = argv[1];
    port_string = argv[2];
  }

  if (CheckIpAddress(ip, port_string)) {
    RunPrompt();
  }

  return 0;
}
