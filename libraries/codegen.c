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
static int unique_label_id = 0;

void generate_expression(ASTNode* node)
{

    if(node->type == AST_INT)
    {
        fprintf(out, "\tpushq $%d\n", node->int_value);
        return;
    }

    if(node->type == AST_VAR_DECL)
    {
        stack_offset += 8;
        vars[var_count].name = node->var_decl.name;
        vars[var_count].offset = stack_offset;
        var_count++;

        fprintf(out, "\tsubq $8, %%rsp\n");
        return;
    }

    if(node->type == AST_ASSIGN)
    {
        generate_expression(node->assign.value);
        fprintf(out, "\tpopq %%rax\n");

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
                fprintf(out, "\tpushq -%d(%%rbp)\n", vars[i].offset);
                break;
            }
        }
        return;
    }

    if(node->type == AST_BINOP)
    {
        if(node->binop.op == TOKEN_AND) {
            int label_false = unique_label_id++;
            int label_end = unique_label_id++;

            generate_expression(node->binop.left);
            fprintf(out, "\tpopq %%rax\n");
            fprintf(out, "\tcmpq $0, %%rax\n");
            fprintf(out, "\tje _and_false_%d\n", label_false);

            generate_expression(node->binop.right);
            fprintf(out, "\tpopq %%rax\n");
            fprintf(out, "\tjmp _and_end_%d\n", label_end);

            fprintf(out, "_and_false_%d:\n", label_false);
            fprintf(out, "\tmovq $0, %%rax\n");

            fprintf(out, "_and_end_%d:\n", label_end);
            fprintf(out, "\tpushq %%rax\n");
            return;
        }
        if(node->binop.op == TOKEN_OR) {
            int label_true = unique_label_id++;
            int label_end = unique_label_id++;

            generate_expression(node->binop.left);
            fprintf(out, "\tpopq %%rax\n");
            fprintf(out, "\tcmpq $0, %%rax\n");
            fprintf(out, "\tjne _or_true_%d\n", label_true);

            generate_expression(node->binop.right);
            fprintf(out, "\tpopq %%rax\n");
            fprintf(out, "\tjmp _or_end_%d\n", label_end);

            fprintf(out, "_or_true_%d:\n", label_true);
            fprintf(out, "\tmovq $1, %%rax\n");

            fprintf(out, "_or_end_%d:\n", label_end);
            fprintf(out, "\tpushq %%rax\n");
            return;
        }

        if (node->binop.op == TOKEN_GT  || node->binop.op == TOKEN_LT ||
            node->binop.op == TOKEN_GTE || node->binop.op == TOKEN_LTE ||
            node->binop.op == TOKEN_EE)
        {
            generate_expression(node->binop.left);
            generate_expression(node->binop.right);
            fprintf(out, "\tpopq %%rbx\n");  // right operand
            fprintf(out, "\tpopq %%rax\n");  // left operand

            switch(node->binop.op)
            {
                case TOKEN_GT:
                    fprintf(out, "\tcmp %%rbx, %%rax\n");
                    fprintf(out, "\tsetg %%al\n");
                    break;
                case TOKEN_LT:
                    fprintf(out, "\tcmp %%rbx, %%rax\n");
                    fprintf(out, "\tsetl %%al\n");
                    break;
                case TOKEN_GTE:
                    fprintf(out, "\tcmp %%rbx, %%rax\n");
                    fprintf(out, "\tsetge %%al\n");
                    break;
                case TOKEN_LTE:
                    fprintf(out, "\tcmp %%rbx, %%rax\n");
                    fprintf(out, "\tsetle %%al\n");
                    break;
                case TOKEN_EE:
                    fprintf(out, "\tcmp %%rbx, %%rax\n");
                    fprintf(out, "\tsete %%al\n");
                    break;
            }

            fprintf(out, "\tmovzbq %%al, %%rax\n");  // zero-extend to 64-bit
            fprintf(out, "\tpushq %%rax\n");
            return;
        }

        if(node->binop.op != TOKEN_AND && node->binop.op != TOKEN_OR)
        {
            generate_expression(node->binop.left);
            generate_expression(node->binop.right);
            fprintf(out, "\tpopq %%rbx\n");
            fprintf(out, "\tpopq %%rax\n");

            switch(node->binop.op)
            {
                case TOKEN_PLUS:  fprintf(out, "\tadd %%rbx, %%rax\n"); break;
                case TOKEN_MINUS: fprintf(out, "\tsub %%rbx, %%rax\n"); break;
                case TOKEN_MULT:  fprintf(out, "\timul %%rbx, %%rax\n"); break;
                case TOKEN_DIVIDE:
                    fprintf(out, "\tmov %%rax, %%rdx\n");
                    fprintf(out, "\tcqo\n");
                    fprintf(out, "\tidiv %%rbx\n");
                    break;
            }

            fprintf(out, "\tpushq %%rax\n");
            return;
        }
    }
}

void generate_statement(ASTNode* node)
{
    if(node->type == AST_PROGRAM)
    {
        for(int i = 0; i < node->program.count; i++)
            generate_statement(node->program.statements[i]);
        return;
    }

    if(node->type == AST_VAR_DECL)
    {
        stack_offset += 8;
        vars[var_count].name = node->var_decl.name;
        vars[var_count].offset = stack_offset;
        var_count++;

        fprintf(out, "\tsubq $8, %%rsp\n");
        return;
    }

    if(node->type == AST_IF)
    {
        int label = unique_label_id++;

        generate_expression(node->if_stmt.condition);
        fprintf(out, "\tpopq %%rax\n");
        fprintf(out, "\tcmpq $0, %%rax\n");
        fprintf(out, "\tje else_%d\n", label);

        generate_statement(node->if_stmt.then_branch);

        fprintf(out, "\tjmp end_if_%d\n", label);
        fprintf(out, "else_%d:\n", label);

        if(node->if_stmt.else_branch)
            generate_statement(node->if_stmt.else_branch);

        fprintf(out, "end_if_%d:\n", label);
        return;
    }

    if(node->type == AST_EXIT)
    {
        generate_expression(node->exit_stmt.expr);
        fprintf(out, "\tpopq %%rdi\n");
        fprintf(out, "\tmovq $60, %%rax\n");
        fprintf(out, "\tsyscall\n");
        return;
    }

    if(node->type == AST_ASSIGN ||
        node->type == AST_BINOP ||
        node->type == AST_VAR ||
        node->type == AST_INT)
    {
        generate_expression(node);
        fprintf(out, "\taddq $8, %%rsp\n");
        return;
    }

    printf("Unknown statement type: %d\n", node->type);
}

void generate_program(ASTNode* node, char* output_name)
{
    char output[256];

    snprintf(output, sizeof(output), "assembling_dir/%s.s", output_name);

    out = fopen(output, "w");
    if (!out)
    {
        printf("Failed to open output file");
        return;
    }

    fprintf(out, ".global _start\n");
    fprintf(out, "_start:\n");
    fprintf(out, "\tpushq %%rbp\n");
    fprintf(out, "\tmovq %%rsp, %%rbp\n");

    generate_statement(node);

    fclose(out);
}
