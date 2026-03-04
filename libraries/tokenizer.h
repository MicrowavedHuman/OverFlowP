#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,
    TOKEN_EXIT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_EOF,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIVIDE,
    TOKEN_EXPO,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_OR,
    TOKEN_AND,
    TOKEN_LT,
    TOKEN_LTE,
    TOKEN_GT,
    TOKEN_GTE,
    TOKEN_EE,
    TOKEN_SEMI
} TokenType;

typedef struct {
    TokenType type;
    char* text;
} Token;

void append_token(Token** list, int* count, int* capacity, Token new_token);
Token tokenize(const char** input_ptr);

#endif
