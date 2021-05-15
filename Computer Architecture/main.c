/*
 * main.c
 *
 * 20493-02 Computer Architecture
 * Term Project on Implentation of Cache Mechanism
 */


#include <stdio.h>
#include "cache_impl.h"

int num_cache_hits = 0;
int num_cache_misses = 0;

int num_bytes = 0;
int num_access_cycles = 0;

int global_timestamp = 0;

int retrieve_data(void *addr, char data_type) {
    int value_returned = -1; /* accessed data/ tag
    /* Invoke check_cache_data_hit() */
	if (check_cache_data_hit(addr, data_type) == -1) {/* In case of the cache miss event, access the main memory by invoking access_memory() */
		printf(" MISS!\n");
		access_memory(addr, data_type);
	}
	return value_returned; 
}


int main(void) {
    FILE *ifp = NULL, *ofp = NULL;
    unsigned long int access_addr; /* byte address (located at 1st column) in "access_input.txt" */
    char access_type; /* 'b'(byte), 'h'(halfword), or 'w'(word) (located at 2nd column) in "access_input.txt" */
    int accessed_data; /* This is the data that you want to retrieve first from cache, and then from memory */ 
    
    init_memory_content();
    init_cache_content();
    
    ifp = fopen("access_input.txt", "r");
    if (ifp == NULL) {
        printf("Can't open input file\n");
        return -1;
    }
    ofp = fopen("access_output.txt", "w");
    if (ofp == NULL) {
        printf("Can't open output file\n");
        fclose(ifp);
        return -1;
    }
    
    /* Fill out here by invoking retrieve_data() */
	int i = 0;
	while (1)
	{
		if (fscanf_s(ifp, "%d %c", &access_addr[i], &access_type[i]) == EOF)break;//파일에서 한줄씩 읽어서 저장 합니다.
		printf("addr:%d, type:%c,block_address:%d, byte_offset:%d, cache_index:%d, tag:%d ", access_addr[i], access_type[i], access_addr[i] / 8, access_addr[i] % 8, (access_addr[i] / 8) % CACHE_SET_SIZE, (access_addr[i] / 8) / CACHE_SET_SIZE);
		retrieve_data((void*)access_addr[i], access_type[i]);
		i++;
	}
	fprintf(ofp, "%d", );

	fclose(ifp);
	fclose(ofp);

	print_cache_entries();
	return 0;

}
