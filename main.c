#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <helper.h>
#include <tokenizer.h>
#include <parser.h>
#include <ast.h>
#include <codegen.h>

#define MAX_TOKENS 10000 // adjust based on expected input size

int main(int argc, char **argv)
{
    int passed; // Custom error handling is implemented with this
    int x;
    int debug; // Whether or not to print debug messages
    int remove_true;
    passed = 1;
    debug = 0;
    remove_true = 1;
    char* output_name = "output";

    if(argc < 2){
        printf("Please at least put in 1 argument.\n");
        passed = 0; // Reports failed
        return(1);
    }

    if(argc > 2)
    {
        if(string_compare(argv[2], "-o") == 1)
        {
            if(argc > 3)
            {
                output_name = strdup(argv[3]);
            }
        }
        if( in_list(argv, argc, "-dra") == 1)
        {
            remove_true = 0;
        }
        if (in_list(argv, argc, "-p") == 1)
        {
            logo_print();
        }
        if (in_list(argv, argc, "-h") == 1 || in_list(argv, argc, "--help"))
        {
            printf("Commands:\n\t1. Help, lists the commands: -h or --help\n\t2. Output, changes the name of the output file: -o\n\t3. Don't Remove Assembly, this flag makes it so that the assembly file doesn't get removed: -dra\n\t4. Print Logo, prints the fancy logo of OverFlowP: -p\n");
            exit(0);
        }
    }
    char* buffer; // Create an array of chars called buffer
    buffer = read_file(argv[1]); // Initliaze buffer!!
    const char* pnter = buffer; // Copy over stuff into pnter
    Token tokens[MAX_TOKENS];
    int token_count = 0;
    Token t; // Declare a token type

    while (1) {
        t = tokenize(&pnter); // Get next token
        if(debug == 1)
        {
            printf("Token: type=%d, text='%s'\n", t.type, t.text);
        }

        tokens[token_count] = t;

        if (t.type == TOKEN_EOF) {
            token_count++;
            break;
        }
        token_count++;
    }

    if(debug == 1)
    {
        for(x=0; x < token_count; x++)
        {
            printf("%s ", type_converter(tokens[x].type));
        }
        printf("\n");
    }
    // Later for AST and Parsing
    system("mkdir -p assembling_dir");


    Parser parser;
    parser.tokens = tokens;
    parser.pos = 0;
    parser.token_count = token_count;

    ASTNode* root = parse_program(&parser);
    generate_program(root, output_name);

    char output[256];
    char cmd[512];
    snprintf(output, sizeof(output), "assembling_dir/%s.s", output_name);
    snprintf(cmd, sizeof(cmd), "gcc %s -o %s -nostdlib", output, output_name);
    system(cmd);

    // Assuming Finished with AST and assembling
    if(passed == 1 && remove_true == 1)
    {
        system("rm -rf assembling_dir");
    }
}
