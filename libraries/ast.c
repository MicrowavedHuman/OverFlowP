#include <stdio.h>
#include <stdlib.h>
#include <ast.h>
#include <string.h>

ASTNode* make_int_node(int value)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_INT;
    node->int_value = value;
    return node;
}

ASTNode* make_binop_node(int op, ASTNode* left, ASTNode* right)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINOP;
    node->binop.op = op;
    node->binop.left = left;
    node->binop.right = right;
    return node;
}

ASTNode* make_exit_node(ASTNode* expr)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_EXIT;
    node->exit_stmt.expr = expr;
    return node;
}

ASTNode* make_var_decl_node(char* name)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VAR_DECL;
    node->var_decl.name = strdup(name);
    return node;
}

ASTNode* make_var_node(char* name)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VAR;
    node->var.name = strdup(name);
    return node;
}

ASTNode* make_assign_node(char* name, ASTNode* value)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGN;
    node->assign.name = strdup(name);
    node->assign.value = value;
    return node;
}

ASTNode* make_program_node()
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_PROGRAM;

    node->program.count = 0;
    node->program.capacity = 4;
    node->program.statements = malloc(sizeof(ASTNode*) * node->program.capacity);

    return node;
}

void add_statement(ASTNode* program, ASTNode* stmt)
{
    if(program->program.count >= program->program.capacity)
    {
        program->program.capacity *= 2;
        program->program.statements =
        realloc(program->program.statements,
                sizeof(ASTNode*) * program->program.capacity);
    }

    program->program.statements[program->program.count++] = stmt;
}
