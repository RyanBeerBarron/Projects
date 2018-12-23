#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "cache.h"
#include "cache_func.h"
#include "cache_util.h"

int n, k, l, a;
cache_t cache;
char* filename;

int main(int argc, char** argv)
{
	int state = ENTRY_STATE;

	printf("Welcome to the cache simulation.\n"
		"Please enter the attributes of the cache you want to simulate, separated by spaces or commas.\n"
		"First enter the number of set, n, then the number of directories, k, the number of bytes per cache line, l. They must be powers of 2.\n"
		"Also specify the size of the addresses (8, 16, 32 or 64 bits).\n"
		"Or enter \"quit\" to leave.\n");
	while(state != EXIT_STATE)
	{
		char string[BUFFER_LENGTH];
		char* temp;
		while(state == ENTRY_STATE){
			// Prepare to get parameters for cache, set them to 0 and allocate space for command line input
			k = 0;
			n = 0;
			l = 0;
			a = 0;
			int temp1 = 0;
			int temp2 = 0;
			int temp3 = 0;
			int temp4 = 0;
			cli_arg_t args;
			args.counter = 0;
			args.vector = malloc(ARGS_NUMBER * sizeof(char*));	
			fgets(string, BUFFER_LENGTH, stdin);		//Take user input and parse it
			int len = strlen(string);
			if(len > 0) {
				string[len-1] = '\0'; // Replace newline at the end of input by a null terminator
			}	
			int rv = parse_cli(string, &args); // Parse the line into multiple strings and get result message
			if (rv == NOTHING) { // In case on only whitespace
			}			
			else if(rv == SUCCES){
				rv = parse_args(&args, state); // Parse the multiple strings  and get result message
				if(rv == EXIT) {
					state = EXIT_STATE;
				}
				else if(rv == ERROR) {
					printf("Invalid argument, please try again.\n");
				}
				else if(rv == SUCCES) {
					for(int i = 0; i<args.counter; i++) {
						switch(i) {
							case 0:
								temp1 = atoi(args.vector[i]);
								break;
							case 1 : 
								temp2 = atoi(args.vector[i]);
								break;
							case 2 :
								temp3 = atoi(args.vector[i]);
								break;
							case 3 : 
								temp4 = atoi(args.vector[i]);
								break;
							default :
								break;				
						}
					}
					if(ispow2(temp1) && ispow2(temp2) && ispow2(temp3) && (temp4 == 8 || temp4 == 16 || temp4 == 32 || temp4 == 64)) {
						if(temp4 > (log2(temp1) + log2(temp2) + log2(temp3))) {
							n = temp1;
							k = temp2;
							l = temp3;
							a = temp4;
							state = INIT_STATE;
						} else {
							printf("Invalid arguments, addresses too small for the cache parameters.\n");
						}
					}
					else {
						printf("Invalid arguments, please enter powers of 2 for n, k and l. And either 8, 16, 32 or 64 for the addresses");
					}		
				}
			}
		}
		while(state == INIT_STATE) {
			verbose = 0;
			file = 0;
			printf("The values of n, k and l are: %d, %d, %d.\n"
					"And the address size is: %d\n", n, k, l, a);
			printf(	"If you want to use the default addresses, enter 0.\n"
					"If you want to manually enter addresses at each step, enter 1.\n"
					"If you want to read addreses from a file enter the path of that file.\n"
					"If you want a trace of the cache simulation add option \"-v\".\n"
					"If you want the trace written in a file, add option \"-f\".\n"
					"Enter \"redo\" to change the cache parameters\n"
					"Enter \"quit\" to leave.\n");
			cli_arg_t args;
			args.counter = 0;
			args.vector = malloc(ARGS_NUMBER * sizeof(char*));
			fgets(string, BUFFER_LENGTH, stdin);
			int rv = parse_cli(string,  &args);
			if (rv == NOTHING) {
			} else if(rv == SUCCES) {
				rv = parse_args(&args, state);
				if(rv == EXIT) {
					state = EXIT_STATE;
				}
				else if(rv == REDO) {
					state = ENTRY_STATE;
				}
				else if (rv == DEFAULT) {
					state = FILE_STATE;
				}
				else if (rv == DEFAULT) {
					state = DEFAULT_STATE;
				}
				else if (rv == MANUAL) {
					state = MANUAL_STATE;
				}
			initialize_cache(&cache, k, n, l);
			print_cache(cache);
			}
		}
	}	
	return 1;
}


