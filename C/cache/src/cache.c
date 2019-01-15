#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
#include "cache.h"
#include "cache_func.h"
#include "cache_util.h"

const char * addresses_8[NUM_ADDRESS] = {"0x00", "0x0a", "0x00", "0xff" };
const char * addresses_16[NUM_ADDRESS] = {"0x0000", "0x000a", "0x0000", "0x00ff" };
const char * addresses_32[NUM_ADDRESS] = {"0x00000000", "0x0000000a", "0x00000000", "0x000000ff" };
const char * addresses_64[NUM_ADDRESS] = {"0x0000000000000000", "0x000000000000000a", "0x0000000000000000", "0x00000000000000ff" };

int main(int argc, char** argv)
{
	unsigned state = ENTRY_STATE;
	printf("Welcome to the cache simulation.\n"
		"Please enter the attributes of the cache you want to simulate, separated by spaces or commas.\n"
		"First enter the number of set, n, then the number of directories, k, the number of bytes per cache line, l. They must be powers of 2.\n"
		"Also specify the size of the addresses (8, 16, 32 or 64 bits).\n"
		"Or enter \"quit\" to leave.\n");
	while(state != EXIT_STATE) {
		verbose = 0;
		file = 0;
		size_t n, k, l, a;
		cache cache;
		cache.init = 0;
		char string[BUFFER_LENGTH];
		FILE* input = NULL; 
		FILE* output = NULL;

		while(state == ENTRY_STATE){
			cli_arg args;
			// Prepare to get parameters for cache, set them to 0 and allocate space for command line input
			k = 0;
			n = 0;
			l = 0;
			a = 0;
			int temp1 = 0;
			int temp2 = 0;
			int temp3 = 0;
			int temp4 = 0;
			

			int rv = get_input(&args, state); // Parse the line into multiple strings and get result message
			if (rv == ERROR) {
				fprintf(stderr, "Exiting... \n");
				return(EXIT_FAILURE);
			} else if (rv == NOTHING) { // In case of only whitespace
			} else if(rv == EXIT) {
					state = EXIT_STATE;
			} else if(rv == INVALID) {
				fprintf(stderr, "Invalid argument, please try again.\n");
			} else if(rv == SUCCESS) {
				for(size_t i = 0; i<args.counter; i++) {
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
				if( !ispow2(temp1) && !ispow2(temp2) && !ispow2(temp3) && (temp4 == 8 || temp4 == 16 || temp4 == 32 || temp4 == 64)) {
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
					printf("Invalid arguments, please enter powers of 2 for n, k and l. And either 8, 16, 32 or 64 for the addresses\n");
				}		
			}
		}
		while(state == INIT_STATE) {
			printf("The values of n, k and l are: %lu, %lu, %lu.\n"
					"And the address size is: %lu\n", n, k, l, a);
			printf(	"If you want to use the default addresses, enter 0.\n"
					"If you want to manually enter addresses at each step, enter 1.\n"
					"If you want to read addreses from a file of addresses separated by newline of spaces, enter the path of that file.\n"
					"If you want a trace of the cache simulation add option \"-v\".\n"
					"If you want the trace written in a file, add option \"-f\".\n"
					"Enter \"redo\" to change the cache parameters\n"
					"Enter \"quit\" to leave.\n"
					"-----------------------------------------------------------------\n");
			cli_arg args;
			int rv = get_input(&args, state);
			if (rv == NOTHING) {
			} else if (rv == ERROR) {	
				fprintf(stderr, "Exiting... \n");
				return(EXIT_FAILURE);
			} else if(rv == EXIT) {
				state = EXIT_STATE;
			} else if(rv == REDO) {
				state = ENTRY_STATE;
			} else if (rv == FILE_MODE) {
				input = fopen(args.vector[0], "r");
				if(!input) {
					fprintf(stderr, "Error, incorrect file name, could not open.\n"
						"Please try again.\n");
					perror("Error trying to open file");
					errno = 0;
				} else {
					state = FILE_STATE;
					printf("SUCCESS, ready to read\n");
				}
			} else if (rv == DEFAULT) {
				state = DEFAULT_STATE;
			} else if (rv == MANUAL) {
				state = MANUAL_STATE;
			}	
			if(file) {
				printf("Test file option\n");
				output = fopen("trace.txt", "w");
				if(!output) {
					fprintf(stderr, "Error, could not open / create output file.\n");
					perror("Error trying to open file");
					fprintf(stderr, "Exiting... \n");
					return(EXIT_FAILURE);	
				}
			}	
			if(initialize_cache(&cache, k, n, l, a) == ERROR) {	
				fprintf(stderr, "Exiting... \n");
				return(EXIT_FAILURE);

			}
		}
		while(state == FILE_STATE || state == DEFAULT_STATE || state == MANUAL_STATE) {
			printf(	"The simulation goes step by step through all the addresses in the file or from the default ones\n"
					"Just enter a newline to step through the next address, or enter a \".\" to complete the whole simulation\n"
					"At any point, you can enter \"print\" to print the cache to see its content and current hit / miss rate\n"
					"Or you can enter \"end\" to stop the simulation, once finished you can repeat the same, do another or exit the program\n"
					"If you are in manual mode, just enter the address in the command line either in binary or hexadecimal form.\n");
			int loop = 1;
			size_t index = 0;
			char* addresses[NUM_ADDRESS];
			switch (cache.a) {
				case 8: 
					for(size_t i = 0; i<NUM_ADDRESS; i++) {
						addresses[i] = addresses_8[i];
					}
					break;
				case 16:
					for(size_t i = 0; i<NUM_ADDRESS; i++) {
						addresses[i] = addresses_16[i];
					}
					break;
				case 32:
					for(size_t i = 0; i<NUM_ADDRESS; i++) {
						addresses[i] = addresses_32[i];
					}
					break;	
				case 64:
					for(size_t i = 0; i<NUM_ADDRESS; i++) {
						addresses[i] = addresses_64[i];
					}
					break;				
				default : 
					break;
			}			 
			while(loop && index < NUM_ADDRESS) {
				cli_arg args;
				int rv = get_input(&args, state);
				if (rv == NOTHING) {
					if(state == DEFAULT_STATE) {
						// Step through next address
						index++;
					} else if (state == FILE_STATE) {
						fgets(string, BUFFER_LENGTH, )
					}
				} else if (rv == PRINT || verbose) {
					print_cache(cache);
				} else if (rv == AUTO) {
					//Go through all the addresses
					print_cache(cache);
					loop = 0;
				} else if (rv == END) {
					loop = 0;
				} else if (rv == ADDRESS) {

				}

 
			}

		}


		if(cache.init) {
			free_cache(&cache);
		}
	}	
	printf("Goodbye.\n");
	return EXIT_SUCCESS;
} 