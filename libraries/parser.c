#include <stdio.h>
#include <stdlib.h>
#include <parser.h>
#include <helper.h>
#include <string.h>

  /////////////////////////////
 //    Utility Functions    //
/////////////////////////////

Token current(Parser* p) {
    return p->tokens[p->pos];
}

void advance(Parser* p) {
    if (p->pos < p->token_count)
        p->pos++;
}

int match(Parser* p, int type) {
    if (current(p).type == type) {
        advance(p);
        return 1;
    }
    return 0;
}

void expect(Parser* p, int type) {
    if (!match(p, type)) {
        printf("Parser error: expected token %s, instead got %s\n", type_converter(type), type_converter(current(p).type));
        exit(1);
    }
}

  /////////////////////////////
 //    Main Parser Stuff    //
/////////////////////////////

ASTNode* parse_expression(Parser* p)
{
    ASTNode* node = parse_term(p);

    while(current(p).type == TOKEN_PLUS || current(p).type == TOKEN_MINUS)
    {
        int op = current(p).type;
        advance(p);

        ASTNode* right = parse_term(p);
        node = make_binop_node(op, node, right);
    }

    return node;
}

ASTNode* parse_term(Parser* p)
{
    ASTNode* node = parse_factor(p);

    while(current(p).type == TOKEN_MULT ||  current(p).type == TOKEN_DIVIDE)
    {
        int op = current(p).type;
        advance(p);

        ASTNode* right = parse_factor(p);
        node = make_binop_node(op, node, right);
    }

    return node;
}

ASTNode* parse_factor(Parser* p)
{
    Token t = current(p);

    if(match(p, TOKEN_INT))
    {
        return make_int_node(atoi(t.text)); // ATOI is just basically int() remember that
    }

    if(match(p, TOKEN_IDENTIFIER))
    {
        return make_var_node(t.text);
    }

    if(match(p, TOKEN_LPAREN))
    {
        ASTNode* node = parse_expression(p);
        expect(p, TOKEN_RPAREN);
        return node;
    }

    // Add better error handling later
    printf("Unexpected char in factor set up");
    exit(1);
}

ASTNode* parse_statement(Parser* p)
{
    if(match(p, TOKEN_EXIT))
    {
        ASTNode* expr = parse_expression(p);
        expect(p, TOKEN_SEMI);
        return make_exit_node(expr);
    }

    if(match(p, TOKEN_INT))
    {
        Token name = current(p);
        expect(p, TOKEN_IDENTIFIER);
        expect(p, TOKEN_SEMI);

        return make_var_decl_node(name.text);
    }

    if(current(p).type == TOKEN_IDENTIFIER)
    {
        Token name = current(p);
        advance(p);

        expect(p, TOKEN_ASSIGN);

        ASTNode* value = parse_expression(p);
        expect(p, TOKEN_SEMI);

        return make_assign_node(name.text, value);
    }

    printf("Unknown Statement\n");
    exit(1);
}

ASTNode* parse_program(Parser* p) {
    ASTNode* program = make_program_node();

    while(current(p).type != TOKEN_EOF) {
        ASTNode* stmt = parse_statement(p);
        add_statement(program, stmt);
    }

    return program;
}
