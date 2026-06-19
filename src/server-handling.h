#ifndef SERVER_HANDLING_H
#define SERVER_HANDLING_H
#include "server.h"
#include "parsing.h"
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
char *handle_api_calls(char *path,STUDENT* std);
char *path_get_req(char *request, int *socket,STUDENT* std);
void handle_get(int *socket, char *request,STUDENT* std);
void handle_post(int *socket, char *request);
void launch(Server *server, char *filename,STUDENT* std);
#endif