#ifndef TOKEN_H
#define TOKEN_H

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

typedef struct {
    TokenType type;
    char* text;
} Token;

void append_token(Token** list, int* count, int* capacity, Token new_token);

Token tokenize(const char** input_ptr);

#endif
