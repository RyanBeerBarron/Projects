#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define BUFFER_LENGTH 500

#define C_DEBUG 1


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

int parse_cli (char* line, cli_arg_t* args)
{
	int counter = 1;
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



int initialize_cache (cache_line_t** cache, int k, int n, int l)
{
	for(int i = 0; i<n; i++)
	{	
		for(int j = 0; j<k; j++)
		{	
			cache_line_t cache_line;
			cache_line.l = l;
			cache_line.tag = -1;
			cache_line.age = 0;
			cache[i][j] = cache_line;
		}
	}
	return 1;
}

int print_cache (cache_line_t** cache, int k, int n)
{	
	for(int i = 0; i<n; i++)
	{	
		for(int j = 0; j<k; j++)
			printf("-------------");
		printf("-\n");
		for(int j = 0; j<k; j++)
		{
			cache_line_t cache_line = cache[i][j];
			printf("| %4x %d ", cache_line.tag, cache_line.age);
		}
		printf("|\n");
		for(int j = 0; j<k; j++)
			printf("-------------");
		printf("-\n\n");
	}
	return 1;
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
			temp3 = 0;
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
			}
		}
		free(args.vector);
	}	

	return 1;

}






	/*
	if(argc != 4)
		return 0;
	else
	{
		int k = atoi(argv[1]);
		int n = atoi(argv[2]);
		int l = atoi(argv[3]);

		cache_t cache;
		cache.k = k;
		cache.n = n;
		cache.l = l;
		
		
		
		cache.cache = malloc(n*(sizeof(cache_line_t*)));
		for(int i=0; i<n; i++)
			cache.cache[i] = malloc(k*sizeof(cache_line_t));
		printf("Size of cache: %lu\n", sizeof(cache_line_t*));
		
		int rv;
		rv = initialize_cache(cache.cache, k, n, l);
		if(rv)
			print_cache(cache.cache, k, n);
		
		free(cache.cache);
		return 1;
	*/
