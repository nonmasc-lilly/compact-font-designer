#include "main.h"

void help();

int main(int argc, char **argv) {
    FILE *fp;
    char  content[0xFF*0x8], *token, *eptr,
          filename[4097] = {0},
          input[5000]    = {0},
          intok[5000]    = {0},
          space[2]       = " ";
    unsigned int tmp, current_char, current_row, i;

    if(argc > 1) {
        for(i=1; i<argc;i++) {
            IFNCMP(argv[i], "-h") {
                help();
                exit(1);
            }
            if(!filename[0]) {
                strcpy(argv[i], filename);
            } else {
                printf("multiple file input (earliest error filename %s)\n", argv[i]);
            }
        }
    }

    for(i=0; i<0xFF*0x8; i++) {
        content[i] = 0;
    } 

    current_char = 'A';
    current_row = 0;
    printf("@@ Lilly Tau\nCompact font designer\n");
    while(1) {
        if(!(*filename)) {
            prompt("FILE? ", filename, 4096);
            filename[4096] = 0;
        }
        prompt("input> ", input, 5000);
        strcpy(intok, input);
        token = strtok(intok, space);
        IFNCMP(token, "switch") {
            token = strtok(NULL, space);
            if(token[0] == '\\') {
                tmp = strtol(token + 1, &eptr, 0);
                if(!(*(token+1)) || *eptr) {
                    printf("could not read argument, (not a number)\n");
                    continue;
                }
                current_char = tmp;
                continue;
            }
            current_char = *token;
        } ELNCMP(token, "row") {
            token = strtok(NULL, space);
            tmp = strtol(token, &eptr, 0);
            if(!(*token) || *eptr) {
                printf("could not read argument, (not a number)\n");
                continue;
            }
            if(tmp > 7) {
                printf("argument too large, (must be 0 -> 7)\n");
                continue;
            }
            current_row = tmp;
        } ELNCMP(token, "write") {
            token = strtok(NULL, space);
            tmp = strtol(token, &eptr, 2);
            if(!(*token) || *eptr) {
                printf("could not read argument, (not a binary number)\n");
                continue;
            }
            if(tmp > 0xFF) {
                printf("argument greater than the 8 bit integer limit (11111111)");
                continue;
            }
            content[current_char*8 + current_row] = *(char*)(&tmp);
            current_row++;
            if(current_row > 7) current_row = 0;
        } ELNCMP(token, "show") {
            for(i=0; i<8; i++) {
                printf("%d: b", i);
                print_byte(content[current_char*8 + i]);
                printf("\n");
            }
        } ELNCMP(token, "load") {
            fp = fopen(filename, "r");
            fread(content, 1, 0xFF*8, fp);
            fclose(fp);
        } ELNCMP(token, "save") {
            fp = fopen(filename, "w");
            fwrite(content, 1, 0xFF*8, fp);
            fclose(fp);
        } ELNCMP(token, "fclose") {
            filename[0]=0;
        } ELNCMP(token, "help") {
            help();
        } ELNCMP(token, "nsexit") {
            prompt("are you sure you would like to exit without saving"
                   " (exit for save)[y/N]\n",
                   input, 5000);
            IFNCMP(input, "y") goto exit_l;
            ELNCMP(input, "Y") goto exit_l;
            else goto noexit_l;
            exit_l: {
                break;
            }
            noexit_l:
        } ELNCMP(token, "exit") {
            prompt("are you sure you would like to save and exit (nsexit for no save) [y/N]\n",
                   input, 5000);
            IFNCMP(input, "y") goto sexit_l;
            ELNCMP(input, "Y") goto sexit_l;
            else goto nosexit_l;
            sexit_l: {
                fp = fopen(filename, "w");
                fwrite(content, 1, 0xFF*8, fp);
                fclose(fp);
                break;
            }
            nosexit_l:
        } ELNCMP(token, "status") {
            printf("filename: %s\n");
            printf("current char: %d\n", current_char);
            printf("current row: %d\n", current_row);
        }
    }
    return 0;
}

void help() {
    printf("@@ Lilly tau\nCompact font designer\n");
    printf("\tthe compact font designer is a program allowing the user\n");
    printf("\tto create files containing 8x8 single color images representing\n");
    printf("\tascii/utf8 character codes, each input file is written as size\n");
    printf("\t%d. In which each character is eight bytes long, allowing for\n", 0xFF*8);
    printf("\t255 characters. The commands for editting a compact_font file\n");
    printf("\tare as follows:\n");
    printf("\t  - switch : changes which character you are editting in the file\n");
    printf("\t  - row    : changes the row of the character you are currently editting\n");
    printf("\t  - write  : sets the current row to an 8 bit binary number and \n");
    printf("\t             increments row\n");
    printf("\t  - show   : prints the current character binary to the screen as\n");
    printf("\t             an 8x8 grid\n");
    printf("\t  - load   : loads the contents of the current file for editting\n");
    printf("\t  - save   : writes the current working memory into the current file\n");
    printf("\t  - fclose : closes the current file and prompts for a new one\n");
    printf("\t  - help   : opens this menu\n");
    printf("\t  - nsexit : exits without saving\n");
    printf("\t  - exit   : exits and saves\n");
    printf("\t  - status : shows various working variables (such as current\n");
    printf("\t             character, file, and row");
}
