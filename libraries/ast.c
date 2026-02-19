#include <stdio.h>
#include <stdlib.h>
#include <ast.h>

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
