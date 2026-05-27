#include <stdio.h>
#include "server.h"

void launch(Server *server){

}

int main()
{

  Server server;
  server = constructor(AF_INET,SOCK_STREAM,0,INADDR_ANY,80,10,launch);

  int clientFD = accept(server.socket_fd, 0, 0); // this is going to return the client fd
  char buffer[256] = {0};

  recv(clientFD, buffer, 256, 0);

  // GET /file.html ..............

  return 0;
}