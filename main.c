#include <stdio.h>
#include "src/server.h"
#include "src/parsing.h"
#include "src/server-handling.h"
#include <stdlib.h>
int main()
{
  char *filename = malloc(256);

  Server server;

  server = constructor(
      AF_INET,
      SOCK_STREAM,
      0,
      INADDR_ANY,
      8080,
      10);

  launch(&server, filename);

  free(filename);

  return 0;
}
