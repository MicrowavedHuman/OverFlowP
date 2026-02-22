#include <stdio.h>
#include <ast.h>
#include <parser.h>
#include <tokenizer.h>

FILE* out;

void generate_expression(ASTNode* node)
{
    if(node->type == AST_INT)
    {
        fprintf(out, "\tmovq $%d, %%rax\n", node->int_value);
    }

    if(node->type == AST_BINOP)
    {
        generate_expression(node->binop.left);
        fprintf(out, "\tpushq %%rax\n");

        generate_expression(node->binop.right);
        fprintf(out, "\tpopq %%rbx\n");

        switch(node->binop.op)
        {
            case TOKEN_PLUS:
                fprintf(out, "\tadd %%rbx, %%rax\n");
                break;

            case TOKEN_MINUS:
                fprintf(out, "\tsub %%rax, %%rbx\n");
                fprintf(out, "\tmov %%rbx, %%rax\n");
                break;

            case TOKEN_MULT:
                fprintf(out, "\timulq %%rbx, %%rax\n");
                break;

            case TOKEN_DIVIDE:
                fprintf(out, "\tmovq %%rax, %%rcx\n");
                fprintf(out, "\tmovq %%rbx, %%rax\n");
                fprintf(out, "\tcqo\n");
                fprintf(out, "\tidivq %%rcx\n");
                break;
        }
        return;
    }
}

void generate_program(ASTNode* node, char* output_name)
{
    char output[256];

    snprintf(output, sizeof(output), "assembling_dir/%s.s", output_name);

    out = fopen(output, "w");
    if (!out)
    {
        printf("Failed to open output file");
    }

    fprintf(out, ".global _start\n");
    fprintf(out, "_start:\n");

    if(node->type == AST_EXIT) {
        generate_expression(node->exit_stmt.expr);

        fprintf(out, "\tmovq %%rax, %%rdi\n");
        fprintf(out, "\tmovq $60, %%rax\n");
        fprintf(out, "\tsyscall\n");
    }

    fclose(out);
}
