#ifndef CODEGEN_H
#define CODEGEN_H

typedef struct {
    char* name;
    int offset;
} Variable;

void generate_expression(ASTNode* node);
void generate_program(ASTNode* node, char* output_name);


#endif
