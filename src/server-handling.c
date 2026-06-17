
#include "server-handling.h"
#include "parsing.h"
static char indexjsonfile[256] = "../database/index.json";
char *handle_api_calls(char *path)
{
    char stdid[256] = {0};
    char rno[256] = {0};

    sscanf(path, "/getstd?stdid=%255[^&]&rno=%255s", stdid, rno);

    char* filename = generate_filename(stdid,rno);
    // implement the file reading and display process
}

char *path_get_req(char *request, int *socket)
{
    char *path = get_first_word(request);

    if (path == NULL)
    {
        printf("PATH ERROR\n");
        return NULL;
    }

    printf("\nPATH::%s\n", path);

    char *response = NULL;

    if (strncmp(path, "/getstd", 7) == 0)
    {
        response = handle_api_calls(path);
    }
    else if (strcmp(path, "/") == 0)
    {
        response = html_return(indexjsonfile);
    }
    else
    {
        response = html_return(indexjsonfile);
    }

    free(path);

    return response;
}

void handle_get(int *socket, char *request)
{
    char *response = path_get_req(request, socket);

    if (response != NULL)
    {

        int w = write(*socket, response, strlen(response));
        if (w==-1)
        {
            printf("\nError in writing the socket in handle_get function in server-handing.c\n");
            exit(EXIT_FAILURE);
        }

        free(response);
    }
}

void handle_post(int *socket, char *request)
{
    char *body = strstr(request, "\r\n\r\n");

    if (body)
    {
        body += 4;
        printf("POST BODY: %s\n", body);
    }

    char *response = json_return("../database/index.json");

    if (response != NULL)
    {
        int w = write(*socket, response, strlen(response));
        if (w==-1)
        {
            printf("\nError in writing the socket in handle_get function in server-handing.c\n");
            exit(EXIT_FAILURE);
        }
        free(response);
    }
}

void launch(Server *server, char *filename)
{
    char *request = malloc(30000);

    if (request == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    while (1)
    {
        printf("===== WAITING FOR CONNECTION =====\n");

        socklen_t addlen = sizeof(server->address);

        int new_socket = accept(
            server->socket_fd,
            (struct sockaddr *)&(server->address),
            (socklen_t *)&addlen);

        if (new_socket < 0)
        {
            printf("Accept failed\n");
            continue;
        }

        int bytes = read(new_socket, request, 29999);

        if (bytes <= 0)
        {
            close(new_socket);
            continue;
        }

        request[bytes] = '\0';

        char method[8] = {0};
        char path[1024] = {0};

        sscanf(request, "%7s %1023s", method, path);

        printf("METHOD :: %s\n", method);
        printf("PATH   :: %s\n", path);

        if (strcmp(method, "POST") == 0)
        {
            handle_post(&new_socket, request);
        }
        else if (strcmp(method, "GET") == 0)
        {
            handle_get(&new_socket, request);
        }

        printf("\nFULL REQUEST:\n%s\n", request);

        close(new_socket);
    }

    free(request);
}

