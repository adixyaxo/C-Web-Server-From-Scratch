#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include <string.h>
#include <stdlib.h>
void launch(Server *server,char* filename)
{
  char buffer[30000];
  while (1)
  {
    printf("===== WAITING FOR CONNECTION =====");
    socklen_t addlen = sizeof(server->address);
    int new_socket = accept(server->socket_fd, (struct sockaddr *)&(server->address), (socklen_t *)&addlen);
    read(new_socket, buffer, 30000);
    printf("\n%s\n", buffer);
    char* hello = html_return(filename);
    write(new_socket, hello, strlen(hello));
    close(new_socket);
    free(hello);
  }
}

char* html_return(char* filename)
{
  FILE *fp = fopen(filename, "r");
  char* html = malloc(10000);
  html[0] = '\0';
  char *request = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/html\r\n"
                  "\r\n";
  strcat(html,request);
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    strcat(html,buffer);
  }
  fclose(fp);
  return html;
};

int main()
{

  char* filename = malloc(256);
  filename = "basic.html";
  char* raw = malloc(10000);
  raw = html_return("basic.html");
  printf("%s\n",raw);
  Server server;
  server = constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 3000, 10);
  launch(&server,filename);

  return 0;
}