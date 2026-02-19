#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Helper functions
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

typedef enum {
    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_EXIT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIVIDE,
    TOKEN_SEMI
} TokenType;

typedef struct{
    TokenType type;
    char* text;
} Token;

int main(int argc, char **argv)
{
    printf("OverFlowP\n");
    if(argc < 2){
        printf("Please at least put in 1 argument.\n");
        return(1);
    }
    else if(string_compare(argv[1], "-h") == 1 || string_compare(argv[1], "--help") == 1){
        printf("Commands:\n\t1. help, lists the commands: -h or --help\n");
        return(1);
    }

    char* buffer;
    buffer = read_file(argv[1]);
    const char* pnter = buffer;

    Token t;

    while (1) {
        t = tokenize(&pnter); // Get next token
        printf("Token: type=%d, text='%s'\n", t.type, t.text);
        free(t.text); // Free the token's text after use

        if (t.type == TOKEN_EOF) {
            break;
        }
    }



}
