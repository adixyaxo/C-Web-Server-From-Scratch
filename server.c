#include <stdio.h>
#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
       #include <arpa/inet.h>



void getdata(Server *server,char* ip_addr)
{
  int SocketFD = socket(server->domain,server->interface,server->protocol);

  char *ip = ip_addr;
  server->address.sin_port = htons(server->port);
  inet_pton(server->domain, ip, (struct sockaddr *)(&server->address.sin_addr));
  server->address.sin_family = server->domain;

  if (connect(SocketFD, (struct sockaddr *)(&server->address), sizeof(server->address)) != 0)
  {
    printf("Connection was not Successful\n");
  }
  else
  {
    printf("Socket created\n");
  }

  char *msg;
  msg = "GET / HTTP/1.1\r\nHost:google.com\r\n\r\n";
  if (send(SocketFD, msg, strlen(msg), 0) == -1)
  {
    printf("Sending failed\n");
  }
  else
  {
    printf("Sending Request Successful\n");
  }

  char buffer[1024];
  if (recv(SocketFD, buffer, sizeof(buffer), 0) == -1)
  {
    printf("Error in reciving\n");
  }
  else
  {
    printf("Reciving Response Successful");
  }
  printf("=>HTML response recived is :: \n%s", buffer);
}

Server constructor(int domain,
                   int service,
                   int protocol,
                   long interface,
                   int port,
                   int backlog)
{
  Server server;
  server.domain = domain;
  server.service = service;
  server.protocol = protocol;
  server.interface = interface;
  server.port = port;
  server.backlog = backlog;
  server.socket_fd = socket(domain, interface, protocol);

  server.address.sin_addr.s_addr = interface;
  server.address.sin_port = htons(port);
  server.address.sin_family = domain;

  server.socket_fd = socket(domain, service, protocol);

  if (server.socket_fd == 0)
  {
    perror("The socket creation failed\n");
    exit(EXIT_FAILURE);
  }

  server.bind_int = bind(server.socket_fd, (struct sockaddr *)(&server.address), sizeof(server.address));

  if (server.bind_int < 0)
  {
    perror("The binding of the socket failed\n");
    exit(EXIT_FAILURE);
  }

  server.listen_int = listen(server.socket_fd, server.backlog);
  if (server.listen_int < 0)
  {
    perror("Listening function failed\n");
    exit(EXIT_FAILURE);
  }

  return server;
};