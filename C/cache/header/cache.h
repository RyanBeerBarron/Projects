#ifndef CACHE_H
#define CACHE_H


#define BUFFER_LENGTH 500
#define ARGS_LENGTH 25
#define ARGS_NUMBER BUFFER_LENGTH/ARGS_LENGTH

#define EXIT 0
#define SUCCES 1
#define NOTHING 2
#define ERROR 3
#define REDO 4

#define DEFAULT 0
#define MANUAL 1
#define FILE_MODE 2

#define EXIT_STATE 0
#define ENTRY_STATE 1
#define INIT_STATE 2
#define DEFAULT_STATE 3
#define MANUAL_STATE 4
#define FILE_STATE 5

int verbose, file;

typedef struct _cache_line {
	int l;
	int tag;
	int age;
} cache_line_t;

typedef struct _cache {
	int k;
	int n;
	int l;
	cache_line_t** cache;
} cache_t;

typedef struct _cli_arg {
	int counter;
	char** vector;
} cli_arg_t;


#endif