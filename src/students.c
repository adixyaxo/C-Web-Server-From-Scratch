#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "students.h"

void student_allocate_mem(STUDENT *std){
  std->name = malloc(256);
  std->roll_no = malloc(256);
  std->email = malloc(256);
  std->notes = malloc(1024);
}

void student_constructor(STUDENT *std,char* name,char* roll_no,char* email,char* notes){
std->name = strdup(name);
std->email = strdup(email);
std->notes = strdup(notes);
std->roll_no = strdup(roll_no);
}