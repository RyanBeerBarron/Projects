#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cache.h"
#include "cache_util.h"



int parse_cli (char* line, cli_arg_t* args)
{
	while(*line == ' ' || *line == '\t')
		line++;
	int length = strlen(line);
	if(length == 0) {
		return NOTHING;
	} else {
		int counter = 1;
		for(char* i = line; *i != '\0' && counter < ARGS_NUMBER; i++)
		{
			if(*i == ' ')
			{
				*i++ = '\0';
				args->vector[counter-1] = malloc(ARGS_LENGTH);
				memcpy(args->vector[counter-1], line, ARGS_LENGTH);  
				counter++;
				while( *i == ' ')
					i++;
				line =  i;
			}	
		}
		args->vector[counter-1] = malloc(ARGS_LENGTH);
		memcpy(args->vector[counter-1], line, ARGS_LENGTH);  
		args->counter = counter;	
		return SUCCES;	
	}
}

int parse_args (cli_arg_t* arguments, int state)
{
	int counter = arguments->counter;
	char** args = arguments->vector;
	if(state == ENTRY_STATE) {
		if(counter == 1) {
			for(char* i = args[0]; *i != '\0'; i++) {
				*i = tolower(*i);
			}
			if(!strcmp(args[0], "quit")) {
				return EXIT;
			} else return ERROR;	
		} else if(counter == 4) {
			int valid_ints = 1;
			for(int i = 0; i < counter; i++){
				int is_integer = 1;
				for(char* j=args[i]; *j != '\0'; j++) {
					if(!isdigit(*j))
						is_integer = 0;
				}
				if(! is_integer)
					valid_ints = 0;
			}
			if(valid_ints)
			return SUCCES;
		}	
		else return ERROR;
	} else if (state == INIT_STATE) {
		if(counter ==  1) {
			for(char* i = args[0]; *i != '\0'; i++) {
				*i = tolower(*i);
			}
			if(!strcmp(args[0], "quit")) {
				return EXIT;
			}
			else if(!strcmp(args[0], "redo")) {
				return REDO;
			}	
		} 
		for(int i = 1; i < counter; i++) {
			if(!strcmp(args[i], "-v")) {
				verbose = 1;
			}
			if(!strcmp(args[i], "-f")) {
				file = 1;	
			}
		}
		if(!strcmp(args[0], "0")){
			return DEFAULT;
		}
		else if(!strcmp(args[0], "1")) {
			return MANUAL;
		} else return FILE_MODE;	
	}
}


int ispow2(int num)
{
	int temp = 1;
	while(temp < num)
	{
		temp = temp * 2;
	}
	if(temp == num)
		return 1;
	else return 0;		
}