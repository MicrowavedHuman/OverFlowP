#!/bin/bash

main_i="main.c" # The name and location of the main.c file
main_o="build/main" # The name and location of the output assembled file

helper="libraries/helper.c"
tokenizer="libraries/tokenizer.c"
ast="libraries/ast.c"

gcc ${main_i} ${helper} ${tokenizer} ${ast} -I libraries -o ${main_o}

./${main_o} $1 $2
