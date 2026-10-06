#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <stdbool.h>

#ifndef MEM_SIZE
#define MEM_SIZE 4096
#endif

static union {
    char bytes[MEM_SIZE];
    int not_used;
} heap;

static bool init = false;

typedef struct Header{
    int prev_size;
	int size; //0 is unused
} Header;

void check_leaks(){
	char* tmp = heap.bytes;
	int cnt = 0;
	int bytes = 0;
	while(tmp < heap.bytes+MEM_SIZE){
		Header *header = (Header*)tmp;
		if(header->size > 0){
			cnt++;
			bytes += header->size;
		}
		tmp = tmp + sizeof(Header) + abs(header->size);
	}
	if(cnt){
		fprintf(stderr, "mymalloc: %d bytes leaked in %d objects.\n", bytes, cnt);
	}
}

void *mymalloc(size_t size, char *file, int line)
{
    if (!init){
		init = true;
		heap.bytes[0] = 't';
		Header *new = (Header*)heap.bytes;
		new->prev_size = 0;
		new->size = -(MEM_SIZE - 8);
		atexit(check_leaks);
    }

	if (size == 0){
		return NULL;
	}
	//check if size is larger then max capacity
	if (size > MEM_SIZE - sizeof(Header)) {
		fprintf(stderr, "malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
		return NULL;
	}

	size_t needed = (size + 7) & ~(size_t)7;
	char *current = heap.bytes;

	while (current < heap.bytes + MEM_SIZE){
		Header *header = (Header *)current;
		int payload = abs(header->size);
		if (header->size < 0 && (size_t)payload >= needed){
			// if theres extra space then set a new header there
			if ((size_t)payload - needed >= sizeof(Header)){
				Header *new_header = (Header *)(current + sizeof(Header) + needed);
				int remaining = payload - (int)needed - (int)sizeof(Header);
				new_header->prev_size = (int)needed;
				new_header->size = -remaining;

				char *next = current + sizeof(Header) + payload;
				if (next < heap.bytes + MEM_SIZE){
					Header *next_header = (Header *)next;
					next_header->prev_size = remaining;
				}
			}

			// if no extra space then size is still equal to needed
			header->size = needed;
			return current + sizeof(Header);
		}
		current += sizeof(Header) + payload;
	}

	fprintf(stderr, "malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
	return NULL;
}

//myfree
void free_error(char *file, int line){
	fprintf(stderr, "free: Inappropriate pointer (%s:%d)", file, line);
	exit(2);
}

void myfree(void *ptr, char *file, int line){
	if((char*)ptr >= heap.bytes + MEM_SIZE) free_error(file, line);

	char* tmp = heap.bytes;
	bool found = false;
	while(tmp < heap.bytes+MEM_SIZE){
		if((char*)ptr < tmp + sizeof(Header)) free_error(file, line);
		if(tmp + sizeof(Header) == ptr){
			Header *header = (Header*)tmp;
			//user may not hold a chunk of length 0
			if(header->size == 0) free_error(file, line);

			found = true;
			break;
		}
		Header *header = (Header*)tmp;
		tmp = tmp + sizeof(Header) + abs(header->size);
	}
	if(!found) free_error(file, line);

	Header *header = (Header*)(ptr - sizeof(Header));
	//check if this chunk is unused
	if(header->size <= 0) free_error(file, line);

	Header *next = (Header*)(ptr + header->size);
	//check if it can merge with the next chunk
	if((char*)next < heap.bytes+MEM_SIZE && next->size <= 0){
		header->size += sizeof(Header) + (-next->size);
	}

	//if header is not the first chunk
	if((char*)header > heap.bytes){
		Header *prev = (Header*)((char*)header - header->prev_size - sizeof(Header));
		//check if it can merge with the previous chunk
		if(prev->size <= 0){
			prev->size = -prev->size; //because ill treat size as positive later
			prev->size += sizeof(Header) + header->size;
			header = prev;
		}
	}

	//change next next chunk's prev_size
	Header *nnext = (Header*)((char*)header + sizeof(Header) + header->size);
	nnext->prev_size = header->size;

	header->size = -header->size;
}
