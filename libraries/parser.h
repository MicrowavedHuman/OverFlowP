#ifndef PARSER_H
#define PARSER_H

#include <tokenizer.h>
#include <ast.h>

typedef struct {
    Token* tokens;
    int pos;
    int token_count;
} Parser;

Token current(Parser* p);
void advance(Parser* p);
int match(Parser* p, int type);
void expect(Parser* p, int type);

ASTNode* parse_expression(Parser* p);
ASTNode* parse_term(Parser* p);
ASTNode* parse_factor(Parser* p);
ASTNode* parse_statement(Parser* p);
ASTNode* parse_program(Parser* p);

#endif
