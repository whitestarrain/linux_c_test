#!/bin/bash

gcc -S ./foo_func -o ./foo_func.s
gcc -S ./global.c -o ./global.s

gcc -g ./variable_address.c -o variable_address
objdump -dS variable_address

gcc ./io_simulate.c -g -o ./io_simulate
objdump -dS io_simulate

gcc ./io_simulate.c -g -O -o ./io_simulate
objdump -dS io_simulate
