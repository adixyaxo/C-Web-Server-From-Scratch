#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

void getdata(int domain, int type, int protocol, char *ip_addr,int port)
{
  int SocketFD = socket(domain, type, protocol);

  char *ip = ip_addr;
  struct sockaddr_in addr;
  addr.sin_port = htons(port);
  inet_pton(domain, ip, (struct sockaddr *)(&addr.sin_addr));
  addr.sin_family = domain;

  if (connect(SocketFD, (struct sockaddr *)(&addr), sizeof(addr)) != 0)
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

int main()
{

  // getdata(AF_INET, SOCK_STREAM, 0, "142.250.188.46",80);

  // printf("\n\n\n\n");

  getdata(AF_INET,SOCK_STREAM,0,"127.0.0.1",3000);

  return 0;
}