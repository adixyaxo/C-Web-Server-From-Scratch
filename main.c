#include <stdio.h>
#include "src/server.h"
#include "src/parsing.h"
#include "src/server-handling.h"
#include "src/students.h"
#include <stdlib.h>

int main()
{
  printf("Starting server...\n");
  char *filename = malloc(256);

  Server server;
  STUDENT* std;
  std = malloc(sizeof(STUDENT));
  student_allocate_mem(std);
  // student_allocate_mem(std);

  server = constructor(
      AF_INET,
      SOCK_STREAM,
      0,
      INADDR_ANY,
      8080,
      10);

  launch(&server, filename,std);

  free(filename);

  return 0;
}
