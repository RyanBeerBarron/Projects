#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include "cache.h"
#include "cache_util.h"



int parse_cli (char* line, cli_arg* args)
{
	while(*line == ' ' || *line == '\t')
		line++;
	int length = strlen(line);
	if(length == 0) {
		return NOTHING;
	} else {
		int counter = 1;
		char* i = line;
		while(*i != '\0' && counter < ARGS_NUMBER) {
			if(*i == ' ') {
				*i = '\0';
				i++;
				memcpy(args->vector[counter-1], line, ARGS_LENGTH);  
				counter++;
				while( *i == ' ')
					i++;
				line =  i;
			} else i++;
		}
		memcpy(args->vector[counter-1], line, ARGS_LENGTH);  
		args->counter = counter;	
		return SUCCESS;	
	}
}

int parse_args (cli_arg* arguments, unsigned state)
{
	if(state == ENTRY_STATE) {
		if(arguments->counter == 1) {
			for(char* i = arguments->vector[0]; *i != '\0'; i++) {
				*i = tolower(*i);
			}
			if(!strcmp(arguments->vector[0], "quit")) {
				return EXIT;
			} else return INVALID;	
		} else if(arguments->counter == 4) {
			int valid_ints = 1;
			for(size_t i = 0; i < arguments->counter; i++){
				int is_integer = 1;
				for(char* j=arguments->vector[i]; *j != '\0'; j++) {
					if(!isdigit(*j))
						is_integer = 0;
				}
				if(! is_integer)
					valid_ints = 0;
			}
			if(valid_ints)
				return SUCCESS;
		}	
		else return INVALID;
	} else if (state == INIT_STATE) {
		if(arguments->counter ==  1) {	
			for(char* i = arguments->vector[0]; *i != '\0'; i++) {
				*i = tolower(*i);
			}
			if(!strcmp(arguments->vector[0], "quit")) {
				return EXIT;
			}
			else if(!strcmp(arguments->vector[0], "redo")) {
				return REDO;
			}	
		} 
		for(size_t i = 1; i < arguments->counter; i++) {
			if(!strcmp(arguments->vector[i], "-v")) {
				verbose = 1;
			}
			if(!strcmp(arguments->vector[i], "-f")) {
				file = 1;	
			}
		}
		if(!strcmp(arguments->vector[0], "0")){
			return DEFAULT;
		}
		else if(!strcmp(arguments->vector[0], "1")) {
			return MANUAL;
		} else return FILE_MODE;	
	} else if (state == FILE_MODE) {
		
	}
}


int ispow2(int num)
{
	int temp = 1;
	while(temp < num && temp < INT_MAX/2) {
		temp = temp * 2;
	}
	if(temp == num)
		return SUCCESS;
	else return INVALID;		
}

int get_input(cli_arg* args, const unsigned state)
{	
	char* string;
	if(!fgets(string, BUFFER_LENGTH, stdin)) { //Take user input and parse it
		fprintf(stderr, "Fgets failed, value of errno: %d\n", errno);
		perror("Error reading from stdin");
		return ERROR;
	}		
	size_t len = strlen(string);
	if(len > 0) {
		string[len-1] = '\0'; // Replace newline at the end of input by a null terminator
	}	
	int rv = parse_cli(string, args);
	if(rv == NOTHING) return NOTHING;
	else if (rv == SUCCESS) return parse_args(args, state);
}

int substring(const char* src, char* dst, size_t start, size_t end) // Retrieves substring in src, from start index (inclusive) up to end index (non included) into dst
{
	size_t len = strlen(src);
	if(end >= len) {
		return ERROR;
	}
	else {
		size_t n = end - start;
		src += start;
	}
}