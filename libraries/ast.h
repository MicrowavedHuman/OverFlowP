#ifndef AST_H
#define AST_H

// Types

typedef enum {
    AST_INT,
    AST_BINOP,
    AST_EXIT
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;

    union {
        // Int Lit
        int int_value;

        // Bin Op
        struct {
            int op;  // Token +, Token -, Token *, etc...
            struct ASTNode *left;
            struct ASTNode *right;
        } binop;

        // Exit Stat
        struct {
            struct ASTNode *expr;
        } exit_stmt;
    };
} ASTNode;

// Functions
ASTNode* make_int_node(int value);
ASTNode* make_binop_node(int op, ASTNode* left, ASTNode* right);
ASTNode* make_exit_node(ASTNode* expr);

#endif
