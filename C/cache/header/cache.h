#ifndef CACHE_H
#define CACHE_H

#include <stdlib.h>

#define BUFFER_LENGTH 500
#define ARGS_LENGTH 25
#define ARGS_NUMBER BUFFER_LENGTH/ARGS_LENGTH

#define ERROR -1
#define SUCCESS 0
#define INVALID 1
#define EXIT 2
#define NOTHING 3
#define REDO 4

#define DEFAULT 5
#define MANUAL 6
#define FILE_MODE 7

#define EXIT_STATE 0
#define ENTRY_STATE 1
#define INIT_STATE 2
#define DEFAULT_STATE 3
#define MANUAL_STATE 4
#define FILE_STATE 5

#define ADDRESS_8 8
#define ADDRESS_16 16
#define ADDRESS_32 32
#define ADDRESS_64 64

#define NUM_ADDRESS 30

unsigned verbose, file;

char* err_str;


typedef struct cache_line cache_line;
struct cache_line {
	size_t l;
	int tag; // unintialized cache line has a negative tag
	int age; // unintialized cache line has a negative age
	size_t address_size;
	char* data;
};

typedef struct cache cache;
struct cache {
	int init;
	size_t k;
	size_t n;
	size_t l;
	size_t min_address_size;
	cache_line** cache;
	unsigned cache_hit;
	unsigned cache_miss;
};

typedef struct cli_arg cli_arg;
struct cli_arg {
	size_t counter;
	char vector[ARGS_NUMBER][ARGS_LENGTH];
};


#endif