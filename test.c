#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include <string.h>
void launch(Server *server)
{
  char buffer[30000];
  while (1)
  {
    printf("===== WAITING FOR CONNECTION =====");
    int addlen = sizeof(server->address);
    int new_socket = accept(server->socket_fd, (struct sockaddr *)&(server->address), (socklen_t *)&addlen);
    read(new_socket, buffer, 30000);
    printf("\n%s\n", buffer);
    char *hello = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/html\r\n"
                  "\r\n"
                  "<html>"
                  "<body>"
                  "<h1>FINALLY BUILT AN HTTP SERVER FROM SCRATCH IN C</h1>"
                  "</body>"
                  "</html>";
    write(new_socket, hello, strlen(hello));
    close(new_socket);
  }
}

int main()
{

  Server server;
  server = constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 3000, 10);
  launch(&server);

  return 0;
}