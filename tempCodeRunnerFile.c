#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include <string.h>
void launch(Server *server){
  char buffer[30000];
  printf("===== WAITING FOR CONNECTION =====");
  int addlen = sizeof(server->address);
  int new_socket = accept(server->socket_fd,(struct sockaddr*)&(server->address),(socklen_t *)&addlen);
  read(new_socket,buffer,30000);
  printf("\n%s\n",buffer);
  char* hello = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length: 88\nContent-Type: text/html\nConnection: Closed\n<!DOCTYPE html><html><head><title>Basic HTML response</title></head><body><h1>This is a very basic html page response send</h1></body></html>" ;
  write(new_socket,hello,strlen(hello));
  close(new_socket);

}

int main()
{

  Server server;
  server = constructor(AF_INET,SOCK_STREAM,0,INADDR_ANY,80,10);
  launch(&server);

  return 0;
}