#include <stdio.h>
#include <ast.h>
#include <parser.h>
#include <tokenizer.h>
#include <codegen.h>
#include <string.h>

FILE* out;

Variable vars[100];
int var_count = 0;
int stack_offset = 0;

void generate_expression(ASTNode* node)
{
    if(node->type == AST_INT)
    {
        fprintf(out, "\tpushq $%d\n", node->int_value); // push int directly to stack
        return;
    }

    if(node->type == AST_VAR_DECL)
    {
        stack_offset += 8;
        vars[var_count].name = node->var_decl.name;
        vars[var_count].offset = stack_offset;
        var_count++;

        fprintf(out, "\tsubq $8, %%rsp\n"); // reserve 8 bytes for variable
        return;
    }

    if(node->type == AST_ASSIGN)
    {
        generate_expression(node->assign.value); // result on stack
        fprintf(out, "\tpopq %%rax\n"); // pop result to store

        for(int i = 0; i < var_count; i++)
        {
            if(strcmp(vars[i].name, node->assign.name) == 0)
            {
                fprintf(out, "\tmovq %%rax, -%d(%%rbp)\n", vars[i].offset);
                break;
            }
        }
        return;
    }

    if(node->type == AST_VAR)
    {
        for(int i = 0; i < var_count; i++)
        {
            if(strcmp(vars[i].name, node->var.name) == 0)
            {
                fprintf(out, "\tpushq -%d(%%rbp)\n", vars[i].offset); // push variable value to stack
                break;
            }
        }
        return;
    }

    if(node->type == AST_BINOP)
    {
        generate_expression(node->binop.left);  // left on stack
        generate_expression(node->binop.right); // right on stack

        fprintf(out, "\tpopq %%rbx\n"); // right operand
        fprintf(out, "\tpopq %%rax\n"); // left operand

        switch(node->binop.op)
        {
            case TOKEN_PLUS:
                fprintf(out, "\tadd %%rbx, %%rax\n");
                break;

            case TOKEN_MINUS:
                fprintf(out, "\tsub %%rbx, %%rax\n"); // left - right
                break;

            case TOKEN_MULT:
                fprintf(out, "\timul %%rbx, %%rax\n");
                break;

            case TOKEN_DIVIDE:
                fprintf(out, "\tmov %%rax, %%rdx\n");
                fprintf(out, "\tcqo\n");             // sign extend
                fprintf(out, "\tidiv %%rbx\n");     // rax / rbx
                break;
        }

        fprintf(out, "\tpushq %%rax\n"); // push result back to stack
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
    fprintf(out, "\tpushq %rbp\n");
    fprintf(out, "\tmovq %rsp, %rbp\n");
    if(node->type == AST_PROGRAM)
    {
        for(int i = 0; i < node->program.count; i++)
        {
            ASTNode* stmt = node->program.statements[i];

            if(stmt->type == AST_EXIT)
            {
                generate_expression(stmt->exit_stmt.expr);

                fprintf(out, "\tmovq %%rax, %%rdi\n");
                fprintf(out, "\tmovq $60, %%rax\n");
                fprintf(out, "\tsyscall\n");
            }
            else
            {
                generate_expression(stmt);
            }
        }
    }

    fclose(out);
}
