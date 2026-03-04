#!/bin/bash
./make.sh testing_files/test.op -o usertrust -dra -p
./usertrust
echo $?
