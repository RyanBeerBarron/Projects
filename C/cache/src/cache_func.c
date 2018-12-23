#include "cache.h"
#include "cache_func.h"
#include <stdio.h>
#include <stdlib.h>

int initialize_cache (cache_t* cache, int k, int n, int l)
{
	cache->n = n;
	cache->k = k;
	cache->l = l;

	cache->cache = malloc(n * sizeof(cache_line_t*));
	for(int i = 0; i<n; i++)
	{	
		cache->cache[i] = malloc(k * sizeof(cache_line_t));
		for(int j = 0; j<k; j++)
		{	
			cache_line_t cache_line;
			cache_line.l = l;
			cache_line.tag = -1;
			cache_line.age = 0;
			cache->cache[i][j] = cache_line;
		}
	}
	return 1;
}

int print_cache (cache_t cache)
{	
	for(int i = 0; i<cache.n; i++)
	{	
		for(int j = 0; j<cache.k; j++)
			printf("-------------");
		printf("-\n");
		for(int j = 0; j<cache.k; j++)
		{
			cache_line_t cache_line = cache.cache[i][j];
			printf("| %4x %d ", cache_line.tag, cache_line.age);
		}
		printf("|\n");
		for(int j = 0; j<cache.k; j++)
			printf("-------------");
		printf("-\n\n");
	}
	return 1;
}
