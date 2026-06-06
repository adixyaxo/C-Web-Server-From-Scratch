#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

char* html_return(char* filename);
char* return_json();

typedef struct Server
{
    int domain;
    int service;
    int protocol;
    long interface;
    int port;
    int backlog;
    int socket_fd;
    int bind_int;
    int listen_int;

    struct sockaddr_in address;

    void (*launch)(struct Server *server);

} Server;

Server constructor(
    int domain,
    int service,
    int protocol,
    long interface,
    int port,
    int backlog
);

#endif