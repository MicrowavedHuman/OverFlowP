#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <helper.h>
#include <tokenizer.h>


void append_token(Token** list, int* count, int* capacity, Token new_token) {
    if (*count >= *capacity) {
        // Increase capacity
        *capacity = (*capacity == 0) ? 4 : (*capacity * 2);
        *list = (Token*)realloc(*list, (*capacity) * sizeof(Token));
        if (*list == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    (*list)[*count] = new_token; // Copy struct
    (*count)++;
}

Token tokenize(const char** input_ptr){
    const char* input = *input_ptr;
    while (*input == ' ' || *input == '\t' || *input == '\n'){
        input++;
    }

    Token token;
    token.text = NULL;

    if (*input == '\0'){
        token.type = TOKEN_EOF;
        token.text =  strdup("EOF");
        return token;
    }

    if (isdigit(*input))
    {
        const char* start = input;
        while (isdigit(*input)) input++;
        int len = input - start;
        token.text = (char*)malloc(len + 1);
        strncpy(token.text, start, len);
        token.text[len] = '\0';
        token.type = TOKEN_INT;
        *input_ptr = input;
        return token;
    }

    if (isalpha(*input))
    {
        const char* start = input;
        while (isalnum(*input) || *input == '_') input++;
        int len = input - start;
        token.text = (char*)malloc(len + 1);
        strncpy(token.text, start, len);
        token.text[len] = '\0';

        if (string_compare(token.text, "exit") == 1){
            token.type = TOKEN_EXIT;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }

        *input_ptr = input;
        return token;
    }

    switch (*input) {
        case '+': token.type = TOKEN_PLUS; token.text = strdup("+"); break;
        case '-': token.type = TOKEN_MINUS; token.text = strdup("-"); break;
        case '*': token.type = TOKEN_MULT; token.text = strdup("*"); break;
        case '/': token.type = TOKEN_DIVIDE; token.text = strdup("/"); break;
        case '(': token.type = TOKEN_LPAREN; token.text = strdup("("); break;
        case ')': token.type = TOKEN_RPAREN; token.text = strdup(")"); break;
        case ';': token.type = TOKEN_SEMI; token.text = strdup(";"); break;
        default:
            printf("Unknown character: %c\n", *input);
            exit(1);
    }
    input++;
    *input_ptr = input;
    return token;
}
