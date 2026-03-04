#ifndef AST_H
#define AST_H

// Types
typedef struct ASTNode ASTNode; // Weird ass thing, but the Stack Overflow gods have spoken

typedef enum {
    AST_INT,
    AST_BINOP,
    AST_EXIT,
    AST_VAR_DECL,
    AST_VAR,
    AST_ASSIGN,
    AST_BLOCK,
    AST_PROGRAM,
    AST_IF
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        int int_value;
        struct {
            int op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;

        struct {
            struct ASTNode* expr;
        } exit_stmt;

        struct {
            char* name;
        } var_decl;

        struct {
            char* name;
        } var;

        struct {
            char* name;
            struct ASTNode* value;
        } assign;

        struct {
            int count;
            int capacity;
            struct ASTNode** statements;
        } program;

        struct {
            struct ASTNode* condition;
            struct ASTNode* then_branch;
            struct ASTNode* else_branch;
        } if_stmt;
    };
} ASTNode;

// Functions
ASTNode* make_program_node();
ASTNode* make_int_node(int value);
ASTNode* make_binop_node(int op, ASTNode* left, ASTNode* right);
ASTNode* make_exit_node(ASTNode* expr);
ASTNode* make_var_decl_node(char* name);
ASTNode* make_var_node(char* name);
ASTNode* make_assign_node(char* name, ASTNode* value);
ASTNode* make_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
void add_statement(ASTNode* program, ASTNode* stmt);

#endif
