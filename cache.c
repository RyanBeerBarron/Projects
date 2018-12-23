#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "cache.h"


int parse_cli (char* line, cli_arg_t* args)
{
	int counter = 2;
	for(char* i = line; *i != '\0'; i++)
	{
		if(*i == ' ')
		{
			*i++ = '\0';
			args->vector[counter-1] = malloc(BUFFER_LENGTH);
			memcpy(args->vector[counter-1], line, BUFFER_LENGTH/10);  
			counter++;
			while( *i == ' ')
				i++;
			line =  i;
		}	
	}
	args->vector[counter-1] = malloc(BUFFER_LENGTH);
	memcpy(args->vector[counter-1], line, BUFFER_LENGTH/10);  
	args->counter = counter;	
#if C_DEBUG	
	printf("Args counter: %d\n", args->counter);
	for(int i = 0; i < counter; i++)
		printf("%s\n", args->vector[i]);
#endif 
	return 1;
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


int main(int argc, char** argv)
{
	int loop = 1;
	int k, n, l, a;
	int temp1, temp2, temp3, temp4;
	int init_cache;
	int verbose, file;
	char* temp;
	cli_arg_t args;

	printf("Welcome to the cache simulation.\n"
		"Please enter the attributes of the cache you want to simulate, separated by spaces or commas.\n"
		"First enter the number of set, n, then the number of directories, k, the number of bytes per cache line, l. They must be powers of 2.\n"
		"Also specify the size of the addresses (8, 16, 32 or 64 bits).\n"
		"Or enter \"quit\" to leave.\n");
	while(loop)
	{
		init_cache = 0;
		k = 0;
		n = 0;
		l = 0;
		a = 0;
		char s[BUFFER_LENGTH];


		while(!init_cache){
			temp1 = 0;
			temp2 = 0;
			temp3 = 1;
			temp4 = 0;
			verbose = 0;
			file = 0;
			args.counter = 0;
			args.vector = malloc(100*sizeof(char*));	

			if(fgets(s, BUFFER_LENGTH, stdin)){		//Take user input and parse it
				int len = strlen(s);

				printf("Length of user input: %d\nFirst character: %d\n", len, s[0]);			

				if(len > 0){
					s[len-1] = '\0';	
					if(parse_cli(s, &args)){

						printf("Arg counter: %d\nFirst character: %d\n", args.counter, s[0]);	
			
						for(int i = 0; i < args.counter; i++){
							temp = args.vector[i];
							printf("Temp is: %s\n", temp);												
							if(args.counter == 1 && s[0] == '\0' && strlen(s) == 0){
							//Do nothing and loop if user enter a newline
								printf("Test newline\n");
							}
							// If one argument and "quit" then quit loop
							else if(args.counter == 1){
								for(char* j = temp; *j != '\0'; j++){
									*j = tolower(*j);
								}
								if(!strcmp(temp, "quit")){								
									printf("Test quit\n");
									loop = 0;
									init_cache = 1;
								}					
							}
							else if(args.counter == 4){
								//For each string in the user input, check if its an integer and then convert it
								int integer = 1;
								for(char* j = temp; *j!= '\0'; j++){
									if(*j == ',' && *(j+1) == '\0')
										j++;
									else if(!isdigit(*j))
										integer = 0;
								}
								if(integer){	
									printf("Is integer.\n");							
									switch (i) {
										case 0:
											temp1 = atoi(temp);
											break;
										case 1:
											temp2 = atoi(temp);
											break;
										case 2:
											temp3 = atoi(temp);
											break;
										case 3:
											temp4 = atoi(temp);
											break;			
										default:
											break;
									}
								}
								if(!integer){		// If argument is not a integer, query new input.
									printf("Invalid input, try again\n");
									i = args.counter+1;			
								}
	
							}
						}
						printf("The value of temps are: %d %d %d %d\n", temp1, temp2, temp3, temp4);
						if(ispow2(temp1) && ispow2(temp2) && ispow2(temp3) && (temp4 == 8 || temp4 == 16 || temp4 == 32 || temp4 == 64)){
							if(temp4 > (log2(temp1) + log2(temp2) + log2(temp3))){
								printf("Succes\n");
								n = temp1;
								k = temp2;
								l = temp3;
								a = temp4;
								init_cache = 1;
							}	
						}
					}
				}
			}
		}	
		if(init_cache) {
			while(loop) {
				printf("The values of n, k and l are: %d, %d, %d\n"
						"And the address size is: %d\n", n, k, l, a);
				printf(	"If you want to use the default addresses, enter 0.\n"
						"If you want to enter addresses at each step, enter 1.\n"
						"If you want to read addreses from a file enter 2.\n"
						"If you want a trace of the cache simulation add option \"-v\".\n"
						"If you want the trace written in a file, add option \"-f\".\n"
						"Enter \"redo\" to change the cache parameters\n"
						"Enter \"quit\" to leave.\n");
				fgets(s, BUFFER_LENGTH, stdin);
				cache_t cache;
				cache.cache = malloc(n*sizeof(cache_line_t*));
				for(int i=0; i<n i++)
					cache.cache[i] = malloc(k*sizeof(cache_line_t));
				initialize_cache(cache.cache, n, k, l);
				printf("Test 10\n");
				print_cache(cache.cache, n, k);
			}
		}
		free(args.vector);
	}	

	return 1;

}



