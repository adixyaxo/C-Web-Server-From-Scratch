#ifndef PARSING_H
#define PARSING_H
#include "string.h"
#include <stdlib.h>
char *get_first_word(char *request);
char *clip_string(char *str, char clip, int instance);
char *name_to_json(char *stdid, char *rno);
void write_string_in_file(char *str, char *filename);
char *generate_filename(char *stdid, char *rno);
#endif