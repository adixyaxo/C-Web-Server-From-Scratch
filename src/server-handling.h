#ifndef SERVER_HANDLING_H
#define SERVER_HANDLING_H
#include "server.h"
#include "parsing.h"
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
char *handle_api_calls(char *path);
char *path_get_req(char *request, int *socket);
void handle_get(int *socket, char *request);
void handle_post(int *socket, char *request);
void launch(Server *server, char *filename);
#endif