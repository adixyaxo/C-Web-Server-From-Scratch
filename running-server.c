#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include <string.h>
#include <stdlib.h>

char *handle_api_calls(char *path)
{
  char *response = json_return("basic.json");
  return response;
}

char *get_first_word(char *request)
{
  char *bigpath = strstr(request, "/");
  char *path = malloc(1000);
  if (sscanf(bigpath, "%99s", path) == 1)
  {
    return path;
  }
  else
    return NULL;
}

char *path_get_req(char *request, int *socket)
{
  char *path = get_first_word(request);
  printf("\nPATH::%s\n", path);
  if (((path[1] == 'a') && (path[2] == 'p')) && (path[3] == 'i'))
  {
    return handle_api_calls(path);
  }
  if (strcmp(path, "/") == 0)
  {
    char *response = html_return("basic.html");
    return response;
  }
  else{
    char *response = html_return("basic.html");
    return response;
  }
    free(path);
}

void handle_get(int *socket, char *request)
{
  char *response = path_get_req(request, socket);
  write(*socket, response, strlen(response));
}

void handle_post(int *socket, char *request)
{
  char *body = strstr(request, "\r\n\r\n");

  if (body)
  {
    body += 4;

    printf("POST BODY: %s\n", body);
  }

  char *response = json_return("basic.json");

  write(*socket, response, strlen(response));
}

void launch(Server *server, char *filename)
{
  char *request = malloc(30000);

  while (1)
  {

    printf("===== WAITING FOR CONNECTION =====");
    socklen_t addlen = sizeof(server->address);
    while (1)
    {
      int new_socket = accept(server->socket_fd, (struct sockaddr *)&(server->address), (socklen_t *)&addlen);

      int bytes = read(new_socket, request, 29999);

      if (bytes <= 0)
      {
        close(new_socket);
        continue;
      }

      request[bytes] = '\0';

      char method[8];
      char path[1024];

      sscanf(request, "%s %s", method, path);

      if (strcmp(method, "POST") == 0)
        handle_post(&new_socket, request);
      else
        handle_get(&new_socket, path);

      printf("\n%s\n", request);

      close(new_socket);
    }
  }
  free(request);
}

int main()
{
  char *filename = malloc(256);
  Server server;
  server = constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10);
  launch(&server, filename);
  free(filename);

  return 0;
}

// get request http://localhost:8080/api?fname=aditya&lname=dagar