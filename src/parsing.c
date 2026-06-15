#include <stdio.h>
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
