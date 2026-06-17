#ifndef STUDENT_H
#define STUDENT_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
  char* name;
  char* roll_no;
  char* email;
  char* notes;

}STUDENT;

void student_allocate_mem(STUDENT *std);
void student_constructor(STUDENT *std,char* name,char* roll_no,char* email,char* notes);
#endif