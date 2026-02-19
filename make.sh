#!/bin/bash

main_i="main.c" # The name and location of the main.c file
main_o="build/main" # The name and location of the output assembled file

gcc ${main_i} libraries/helper.c libraries/tokenizer.c -I libraries -o ${main_o}

./${main_o} $1 $2
