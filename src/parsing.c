#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"
#include "parsing.h"

void replace_char(char *str, char old_char, char new_char) {
    char *ptr = str;
    while ((ptr = strchr(ptr, old_char)) != NULL){
        *ptr = new_char;  // Dereference pointer to replace the character
        ptr++;            // Move to next position to avoid re-checking the same index
    }
}

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

char *to_json(char *name, char *rno,char *email,char* notes)
{
    char *json = malloc(256);

    if (json == NULL)
        return NULL;

    strcpy(json, "{");
    strcat(json, "\"name\":\"");
    strcat(json, name);
    strcat(json, "\",\"roll_no\":\"");
    strcat(json, rno);
    strcat(json, "\",\"email\":\"");
    strcat(json, email);
    strcat(json, "\",\"notes\":\"");
    strcat(json, notes);
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

char *generate_filename(char *name, char *rno)
{
    char *filename = malloc(256);

    if (filename == NULL)
        return NULL;
        strcpy(filename, name);
        strcat(filename, "-");
        strcat(filename, rno);
        strcat(filename, ".json");
        printf("Filename::%s\n",filename);

    return filename;
}

char *student_detail_page(STUDENT *std)
{
    PrintStudentInfo(std);
    const char *html = {"HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "\r\n"
                        "<!DOCTYPE html>\n"
                        "<html lang=\"en\">\n"
                        "<head>\n"
                        "<meta charset=\"UTF-8\">\n"
                        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                        "<title>Student Details</title>\n"
                        "\n"
                        "<style>\n"
                        "*{\n"
                        "    margin:0;\n"
                        "    padding:0;\n"
                        "    box-sizing:border-box;\n"
                        "    font-family:Inter,sans-serif;\n"
                        "}\n"
                        "\n"
                        "body{\n"
                        "    background:#000;\n"
                        "    color:#fff;\n"
                        "    min-height:100vh;\n"
                        "    display:flex;\n"
                        "    justify-content:center;\n"
                        "    align-items:center;\n"
                        "    padding:30px;\n"
                        "}\n"
                        "\n"
                        ".card{\n"
                        "    width:100%;\n"
                        "    max-width:700px;\n"
                        "    border:1px solid #161616;\n"
                        "    background:#050505;\n"
                        "    padding:50px;\n"
                        "}\n"
                        "\n"
                        ".label{\n"
                        "    color:#666;\n"
                        "    text-transform:uppercase;\n"
                        "    letter-spacing:2px;\n"
                        "    font-size:.75rem;\n"
                        "    margin-bottom:12px;\n"
                        "}\n"
                        "\n"
                        "h1{\n"
                        "    font-size:3rem;\n"
                        "    margin-bottom:40px;\n"
                        "    letter-spacing:-2px;\n"
                        "}\n"
                        "\n"
                        ".row{\n"
                        "    padding:18px 0;\n"
                        "    border-bottom:1px solid #111;\n"
                        "}\n"
                        "\n"
                        ".key{\n"
                        "    color:#666;\n"
                        "    font-size:.85rem;\n"
                        "    margin-bottom:8px;\n"
                        "    text-transform:uppercase;\n"
                        "}\n"
                        "\n"
                        ".value{\n"
                        "    color:#fff;\n"
                        "    font-size:1.05rem;\n"
                        "}\n"
                        "\n"
                        "</style>\n"
                        "</head>\n"
                        "<body>\n"
                        "\n"
                        "<div class=\"card\">\n"
                        "\n"
                        "    <div class=\"label\">Student Record</div>\n"
                        "    <h1>Student Details</h1>\n"
                        "\n"
                        "    <div class=\"row\">\n"
                        "        <div class=\"key\">Name</div>\n"
                        "        <div class=\"value\">%s</div>\n"
                        "    </div>\n"
                        "\n"
                        "    <div class=\"row\">\n"
                        "        <div class=\"key\">Roll Number</div>\n"
                        "        <div class=\"value\">%s</div>\n"
                        "    </div>\n"
                        "\n"
                        "    <div class=\"row\">\n"
                        "        <div class=\"key\">Email</div>\n"
                        "        <div class=\"value\">%s</div>\n"
                        "    </div>\n"
                        "\n"
                        "    <div class=\"row\">\n"
                        "        <div class=\"key\">Notes</div>\n"
                        "        <div class=\"value\">%s</div>\n"
                        "    </div>\n"
                        "\n"
                        "</div>\n"
                        "\n"
                        "</body>\n"
                        "</html>\n"};
    char *response = malloc(10000);
    sprintf(response, html, std->name, std->roll_no, std->email, std->notes);
    return response;
}

void json_to_string(char *filename, STUDENT *std)
{
    printf("Reading student details from file: %s\n", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
    char buffer[10000];
    char *result = fgets(buffer, sizeof(buffer), fp);
    printf("BUFFER:\n[%s]\n", buffer);

    if (result != NULL)
    {
        int ret = sscanf(buffer,
                         "{\"name\":\"%255[^\"]\",\"roll_no\":\"%255[^\"]\",\"email\":\"%255[^\"]\",\"notes\":\"%1023[^\"]\"}",
                         std->name,
                         std->roll_no,
                         std->email,
                         std->notes);

        if (ret != 4)
        {
            printf("Error parsing file\n");
        }
    }

    fclose(fp);
}

void StudentInfoRegistration(char* body){
char name[256];
char rno[256];
char email[256];
char notes[1024];
sscanf(body,"name=%255[^&]&rno=%255[^&]&email=%255[^&]&notes=%1023[^&]",name,rno,email,notes);
replace_char(name,'+',' ');
replace_char(notes,'+',' ');
char* filename = malloc(256);
strcat(filename,"./database/");
strcat(filename,generate_filename(name,rno));
printf("\n\nFILENAME :: %s\n\n",filename);
char* json = to_json(name,rno,email,notes);
printf("JSON :: %s",json);
write_string_in_file(json,filename);
free(filename);
free(json);
}

/* FOR DEBUGGING */

void PrintStudentInfo(STUDENT *std)
{
    printf("Student Name :: %s\nStudent email :: %s\nRoll-no :: %s\nNotes :: %s\n", std->name, std->email, std->roll_no, std->notes);
}