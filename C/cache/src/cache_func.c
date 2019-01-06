#include "cache.h"
#include "cache_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

int initialize_cache (cache* cache, size_t k, size_t n, size_t l, size_t a)
{
	cache->n = n;
	cache->k = k;
	cache->l = l;
	cache->min_address_size = log2(n) + log2(l) + log2(k);
	cache->cache = malloc(n * sizeof(cache_line*));
	if(!cache->cache) {
			fprintf(stderr, "Malloc failed, value of errno: %d\n", errno);
			perror("Error allocating memory");
			return ERROR;
	}
	for(size_t i = 0; i<n; i++)
	{	
		cache->cache[i] = malloc(k * sizeof(cache_line));
		if(!cache->cache[i]) {
			fprintf(stderr, "Malloc failed, value of errno: %d\n", errno);
			perror("Error allocating memory");
			return ERROR;
		}
		for(size_t j = 0; j<k; j++)
		{	
			cache_line cache_line;
			cache_line.address_size = a;
			cache_line.l = l;
			cache_line.tag = -1;
			cache_line.age = -1;
			cache->cache[i][j] = cache_line;
		}
	}
	cache->cache_hit = 0;
	cache->cache_miss = 0;
	cache->init = 1;
	return 0;
}

int print_cache (cache cache)
{	
	for(size_t i = 0; i<cache.n; i++)
	{	
		for(size_t j = 0; j<cache.k; j++)
			printf("-------------");
		printf("-\n");
		for(size_t j = 0; j<cache.k; j++)
		{
			cache_line cache_line = cache.cache[i][j];
			printf("| %4x %d ", cache_line.tag, cache_line.age);
		}
		printf("|\n");
		for(size_t j = 0; j<cache.k; j++)
			printf("-------------");
		printf("-\n\n");
	}
	return 1;
}

int write_cache (cache* cache, const char* address, const char* data)
{
	size_t len = strlen(address);
	if(cache->min_address_size < len)
		return ERROR;
	else if(is_valid_address(address)){
		return ERROR;
	} else {
		size_t data_len = strlen(data);

		size_t tag_length = log2(cache->k);
		size_t set_length = log2(cache->n);
		size_t offset_length = log2(cache->l);

		size_t offset_start = len ;
		size_t set_start = offset_start - offset_length;
		size_t tag_start = set_start - set_length;
		size_t tag_end = tag_start - tag_length;

		char* set = address + tag_start;
		strncpy(set, set, set_length);

		char* tag = tag_end ;
		strncpy(tag, tag, tag_length);

		char* offset = address + set_start ;
		strncpy(offset, offset, offset_length);

		size_t set_num = convert_bool_string(set);
		size_t tag_num = convert_bool_string(tag);
		size_t offset_num = convert_bool_string(offset);
		if(!(offset_num % data_len == 0)) {
			printf("Data not aligned in cache.\n");
			return ERROR;
		}

		for(size_t i = 0; i<cache->k; i++) {
			cache_line cache_line = cache->cache[set_num][i];
			if (cache_line.tag < 0) {
				cache_line.age = 0;
				cache_line.tag = tag_num;
				i = cache->k;
				strncpy(cache_line.data + offset_num, data, data_len);
			} else if(cache_line.age == cache->k) {
				cache_line.age = 0;
				cache_line.tag = tag_num;
				i = cache->k;
				strncpy(cache_line.data + offset_num, data, data_len);
			}
			if (cache_line.age >= 0) {
				cache_line.age++;
			}
		}
		return SUCCESS;
 	}
}

int retrieve_cache(cache* cache, const char* address, char* data, size_t size)
{
	size_t len = strlen(address);
	if(cache->min_address_size < len)
		return ERROR;
	else if(is_valid_address(address)){
		return ERROR;
	} else {
		size_t data_len = strlen(data);

		size_t tag_length = log2(cache->k);
		size_t set_length = log2(cache->n);
		size_t offset_length = log2(cache->l);

		size_t offset_start = len ;
		size_t set_start = offset_start - offset_length;
		size_t tag_start = set_start - set_length;
		size_t tag_end = tag_start - tag_length;

		char* set = address + tag_start;
		strncpy(set, set, set_length);

		char* tag = tag_end ;
		strncpy(tag, tag, tag_length);

		char* offset = address + set_start ;
		strncpy(offset, offset, offset_length);

		size_t set_num = convert_bool_string(set);
		size_t tag_num = convert_bool_string(tag);
		size_t offset_num = convert_bool_string(offset);

		if(!(offset_num % size == 0)) {
			printf("Data not aligned in cache.\n");
			return ERROR;
		}

		for(size_t i = 0; i<cache->k; i++) {
			cache_line cache_line = cache->cache[set_num][i];
			if(cache_line.tag == tag_num) {
				strncpy(data, cache_line.data + offset_num, size);
				return 0;
			}
		}
		return 1;
	}	
}


int free_cache(cache* cache)
{
	for(size_t i =0; i < cache->n; i++) {	
		free(cache->cache[i]);
	}
	free(cache->cache);
	return SUCCESS;
}

int is_valid_address(char const * address)
{
	size_t len = strlen(address);
	if(!(len == ADDRESS_8 || len == ADDRESS_16 || len == ADDRESS_32 || len == ADDRESS_64)) {
		return ERROR;
	}  else return SUCCESS;
}

size_t convert_bool_string(char const * string)
{
	size_t ret = 0;
	for(char* i = string; *i != 0; i++)
	{
		ret *= 2;
		if(*i == '1') {
			ret++;
		}
	}
	return ret;
}