#ifndef CACHE_UTIL_H
#define CACHE_UTIL_H

int parse_cli (char* line, cli_arg_t* args);

int parse_args (cli_arg_t* args, int state);

int ispow2(int num);

#endif