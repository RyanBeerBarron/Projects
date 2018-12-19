#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_LENGTH 500
#define ADDRESSES {0x0000, 0x000c, 0x0008;}

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

int initialize_cache (cache_line_t** cache, int k, int n, int l)
{
	for(int i = 0; i<n; i++)
	{
		//printf("test2\n");	
		for(int j = 0; j<k; j++)
		{	
			cache_line_t cache_line;
			cache_line.l = l;
			cache_line.tag = -1;
			cache_line.age = 0;
			cache[i][j] = cache_line;
			//printf("	test1\n");
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
//Insert arguments K,N,L in that order
int main(int argc, char** argv)
{
	int loop = 1;
	int input = 1;
	int k, n, l;
	int temp1, temp2, temp3;
	int init_cache;
	char temp[BUFFER_LENGTH];
	printf("Welcome to the cache simulation.\n"
		"Please enter the attributes of the cache you want to simulate, separated by spaces or commas.\n"
		"First enter the number of set, n, then the number of directories, k, and the number of bytes per cache line, l.\n"
		"Or enter \"quit\" to leave.\n");
	while(loop)
	{
		init_cache = 0;
		k = 0;
		n = 0;
		l = 0;
		char s[BUFFER_LENGTH];
		
		if(fgets(s, BUFFER_LENGTH, stdin))
		{
			if(sscanf(s, "%s", temp))
				if(!strcmp(temp, "quit"))
					loop = 0;
			if(sscanf(s, "%d %d %d", &temp1, &temp2, &temp3) == 3){
				if(temp1 > 0 && temp2 > 0 && temp3 > 0){
					n = temp1;
					k = temp2;
					l = temp3;
					printf("Test1\n");
					init_cache = 1;
				}	
			}
			else if(sscanf(s, "%d, %d, %d", &temp1, &temp2, &temp3) == 3){
				if(temp1 > 0 && temp2 > 0 && temp3 > 0){
					n = temp1;
					k = temp2;
					l = temp3;
					printf("Test2\n");
					init_cache = 1;
				}	
			}	
			else if(sscanf(s,"%d", &temp1) == 1)
			{
				printf("k=");
				fgets(s, BUFFER_LENGTH, stdin);
				sscanf(s,"%d", &temp2);
				printf("l=");
				fgets(s, BUFFER_LENGTH, stdin);
				sscanf(s,"%d", &temp3);
				if(temp1 > 0 && temp2 > 0 && temp3 > 0){
					n = temp1;
					k = temp2;
					l = temp3;
					printf("Test3\n");
					init_cache = 1;
				}
			}
			else printf("Invalid input, try again\n");
		}
		if(init_cache)
		{
			printf("The values of n, k and l are: %d, %d, %d\n", n, k, l);
			printf(	"If you want to use the default addresses, enter 0.\n"
					"If you want to enter addresses at each step, enter 1.\n"
					"If you want to read addreses from a file enter 2.\n"
					"Also, if you want a trace of the cache simulation add option \"-t\".\n"
					"Enter \"quit\" to leave.\n");
			fgets(s, BUFFER_LENGTH, stdin);
			if(sscanf())
		}	
	}	

	return 1;


















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
}