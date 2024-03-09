#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAIN_H
#define MAIN_H
#define IFNCMP(a, b) if(!strcmp((a), (b)))
#define ELNCMP(a, b) else IFNCMP(a, b)
void prompt(char *prompt_str, char *output, unsigned int len);
void print_byte(char byte);

#endif
