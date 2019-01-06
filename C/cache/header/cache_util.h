#ifndef CACHE_UTIL_H
#define CACHE_UTIL_H

#include <stdio.h>

int parse_cli (char* line, cli_arg* args);

int parse_args (cli_arg* args, unsigned state);

int ispow2(int num);

int get_input(cli_arg* args, unsigned state);

#endif