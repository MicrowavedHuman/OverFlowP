#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <helper.h>
#include <tokenizer.h>

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

    char* buffer;
    buffer = read_file(argv[1]);
    const char* pnter = buffer;

    Token t;

    while (1) {
        t = tokenize(&pnter); // Get next token
        printf("Token: type=%d, text='%s'\n", t.type, t.text);
        free(t.text); // Free the token's text after use

        if (t.type == TOKEN_EOF) {
            break;
        }
    }



}
