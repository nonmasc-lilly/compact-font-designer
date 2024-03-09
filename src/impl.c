#include "main.h"

void prompt(char *prompt_str, char *output, unsigned int len) {
    printf("%s", prompt_str);
    fflush(stdout);
    fgets(output, len, stdin);
    output[strlen(output)-1] = '\0';
}
void print_byte(char byte) {
    unsigned int i;
    for(i=7; i<-1; i--) {
        printf("%d", (byte >> i) & 1);
    }
}
