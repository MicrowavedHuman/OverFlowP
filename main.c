#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <helper.h>
#include <tokenizer.h>

#define MAX_TOKENS 10000 // adjust based on expected input size

int main(int argc, char **argv)
{
    printf("OverFlowP\n");
    if(argc < 2){
        printf("Please at least put in 1 argument.\n");
        return(1);
    }
    else if(string_compare(argv[1], "-h") == 1 || string_compare(argv[1], "--help") == 1){
        printf("Commands:\n\t1. help, lists the commands: -h or --help\n");
        return(1);
    }

    char* buffer; // Create an array of chars called buffer
    buffer = read_file(argv[1]); // Initliaze buffer!!
    const char* pnter = buffer; // Copy over stuff into pnter
    Token tokens[MAX_TOKENS];
    int token_count = 0;
    Token t; // Declare a token type

    while (1) {
        t = tokenize(&pnter); // Get next token
        printf("Token: type=%d, text='%s'\n", t.type, t.text);

        tokens[token_count] = t;

        free(t.text); // Free the token's text after use
        if (t.type == TOKEN_EOF) {
            token_count++;
            break;
        }
        token_count++;
    }

    // Later for AST
    system("mkdir -p assembling_dir");

    // Assuming Finished with AST and assembling
    system("rm -rf assembling_dir");
}
