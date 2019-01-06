#ifndef CACHE_FUNC_H
#define CACHE_FUNC_H

int initialize_cache (cache* cache, size_t k, size_t n, size_t l, size_t address_size);

int free_cache (cache* cache);

int print_cache (cache cache);

int is_valid_address(const char* address);

int write_cache(cache* cache, const char* address, const char* data);

int retrieve_cache(cache* cache, const char* address, char* data, size_t size);

size_t convert_bool_string(const char* address);

#endif
