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
std->name = name;
std->email = email;
std->notes = notes;
std->roll_no = roll_no;
}