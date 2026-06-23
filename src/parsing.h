#ifndef PARSING_H
#define PARSING_H
#include "string.h"
#include <stdlib.h>
#include "students.h"
void replace_char(char *str, char old_char, char new_char);
char *get_first_word(char *request);
char *clip_string(char *str, char clip, int instance);
char *to_json(char *name, char *rno,char *email,char* notes);
void write_string_in_file(char *str, char *filename);
char *generate_filename(char *stdid, char *rno);
char *student_detail_page(STUDENT *std);
void json_to_string(char *filename,STUDENT *std);
void PrintStudentInfo(STUDENT* std);
void StudentInfoRegistration(char* body);
#endif