#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <helper.h>

int string_compare(char *string1, char *string2)
{
    int i = 0;
    while (string1[i] != '\0' && string2[i] != '\0') {
        if (string1[i] != string2[i]) {
            return 0;
        }
        i++;
    }
    return string1[i] == string2[i];
}

char* read_file(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("Failed to open file: %s\n", filepath);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(filesize + 1);
    if (!buffer) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    size_t read_size = fread(buffer, 1, filesize, file);
    if (read_size != filesize) {
        printf("Failed to read file completely\n");
        exit(1);
    }

    buffer[filesize] = '\0';
    fclose(file);
    return buffer;
}

int file_sb(const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("Failed to open file: %s\n", filepath);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    return filesize;
}


char* type_list[] = {"TOKEN_INT", "TOKEN_IDENTIFIER", "TOKEN_EXIT", "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_EOF", "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_MULT", "TOKEN_DIVIDE", "TOKEN_SEMI"};

char* type_converter(int type)
{
    return type_list[type];
}
