
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include <string.h>
#include <stdlib.h>

char *get_first_word(char *request)
{
    char *bigpath = strstr(request, "/");

    if (bigpath == NULL)
        return NULL;

    char *path = malloc(1000);

    if (path == NULL)
        return NULL;

    if (sscanf(bigpath, "%999s", path) == 1)
    {
        return path;
    }

    free(path);
    return NULL;
}

char *clip_string(char *str, char clip, int instance)
{
    char *copy = malloc(strlen(str) + 1);

    if (copy == NULL)
        return NULL;

    strcpy(copy, str);

    for (int i = 0; copy[i] != '\0'; i++)
    {
        if (copy[i] == clip)
        {
            instance--;

            if (instance == 0)
            {
                copy[i] = '\0';
                break;
            }
        }
    }

    return copy;
}

char *name_to_json(char *stdid, char *rno)
{
    char *json = malloc(256);

    if (json == NULL)
        return NULL;

    strcpy(json, "{");
    strcat(json, "\"first-name\":\"");
    strcat(json, stdid);
    strcat(json, "\",\"last-name\":\"");
    strcat(json, rno);
    strcat(json, "\"}");

    return json;
}

void write_string_in_file(char *str, char *filename)
{
    FILE *fp = fopen(filename, "w");

    if (fp != NULL)
    {
        fprintf(fp, "%s", str);
        fclose(fp);
    }
    else
    {
        printf("Error writing file\n");
    }
}

char *generate_filename(char *stdid, char *rno)
{
    char *filename = malloc(256);

    if (filename == NULL)
        return NULL;

    strcpy(filename, stdid);
    strcat(filename, "-");
    strcat(filename, rno);
    strcat(filename, ".json");

    return filename;
}

char *handle_api_calls(char *path)
{
    char stdid[256] = {0};
    char rno[256] = {0};

    sscanf(path, "/getstd?stdid=%255[^&]&rno=%255s", stdid, rno);

    printf("Student ID :: %s\n", stdid);
    printf("Roll No    :: %s\n", rno);

    char *json = name_to_json(stdid, rno);

    if (json == NULL)
        return NULL;

    char *file = generate_filename(stdid, rno);

    if (file == NULL)
    {
        free(json);
        return NULL;
    }

    write_string_in_file(json, file);

    free(json);

    char *response = json_return(file);

    free(file);

    return response;
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
        response = html_return("index.html");
    }
    else
    {
        response = html_return("index.html");
    }

    free(path);

    return response;
}

void handle_get(int *socket, char *request)
{
    char *response = path_get_req(request, socket);

    if (response != NULL)
    {
        write(*socket, response, strlen(response));
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

    char *response = json_return("index.json");

    if (response != NULL)
    {
        write(*socket, response, strlen(response));
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

int main()
{
    char *filename = malloc(256);

    Server server;

    server = constructor(
        AF_INET,
        SOCK_STREAM,
        0,
        INADDR_ANY,
        8080,
        10);

    launch(&server, filename);

    free(filename);

    return 0;
}

