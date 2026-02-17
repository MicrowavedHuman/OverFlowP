#include <stdio.h>


typedef enum {
    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_RET,
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

Token tokenize(const char** input){
    const char* input = *input_ptr;
    while (*input == ' ' || *input == "\t" || *input == "\n"){
        input++;
    }

    Token token;
    token.text = NULL;

    if (*input == '\0'){
        token.type = TOKEN_EOF;
        token.text =  strdup
    }

    if (isdigit(*input))
    {

    }
}

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

int main(int argc, char **argv)
{
    printf("OverFlowP\n");
    if(argc < 2){
        printf("Please at least put in 1 argument.\n");
    }
    else if(string_compare(argv[1], "-h") == 1 || string_compare(argv[1], "--help") == 1){
        printf("Commands:\n\t1. help, lists the commands: -h or --help\n");
    }



}
