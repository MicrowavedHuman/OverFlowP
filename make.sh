#!/bin/bash

#####################
#     Main Vars     #
#####################
main_i="main.c" # The name and location of the main.c file
main_o="build/main" # The name and location of the output assembled file

###################################
#     Extra Library Locations     #
###################################
helper="libraries/helper.c"
tokenizer="libraries/tokenizer.c"
ast="libraries/ast.c"
parser="libraries/parser.c"

####################
#     GCC Call     #
####################
gcc ${main_i} ${helper} ${tokenizer} ${ast} ${parser} -I libraries -o ${main_o}


#######################
#     Calling OFP     #
#######################
./${main_o} $1 $2
