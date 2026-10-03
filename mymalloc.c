#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <stdbool.h>
// initialize
#define MEM_SIZE 4096

//char heap[MEM_SIZE];//pdf 有要求建立heap的方式

static union {
    char bytes[MEM_SIZE];
    double not_used;
} heap;


static int init = 0;

static void initialize(void);

//mymalloc

typedef struct Header{
    int prev_size;  
	int size;
} Header;

void *mymalloc(size_t size, char *file, int line)
{
    if (init == 0) {
        initialize();
    }

	 if (size == 0) {
        return NULL;
    }
	size_t needed = (size + 7) & ~(size_t)7;

	char *current = heap.bytes;

	while (current < heap.bytes + MEM_SIZE) { //不讓他超過memsize
    Header *header = (Header *)current;

	
    int payload = abs(header->size);//確認狀態是否是used

    if (header->size < 0 && (size_t)payload>= needed) {
        if ((size_t)payload - needed >= sizeof(Header) + 8) {

        // 建立unused chunk
        Header *new_header =
            (Header *)(current + sizeof(Header) + needed);

        int remaining =
            payload - (int)needed - (int)sizeof(Header);

        // 建立 B：設定unused chunk
        new_header->prev_size = (int)needed;
        new_header->size = -remaining;

        // 更新chunk A 的size
        header->size = (int)needed;

        // 若是 chunk B 後面還有chunk 的話需要更新 chunk C的prev_size
        char *next = current + sizeof(Header) + payload;

        if (next < heap.bytes + MEM_SIZE) {
            Header *next_header = (Header *)next;
            next_header->prev_size = remaining;
        }

    	} else {
        // 剩下的空間不夠chunk B就整塊攏厚伊
        header->size = payload;
    	}

    return current + sizeof(Header);
	}
    
    current += sizeof(Header) + payload;
	}
	if (size > MEM_SIZE - sizeof(Header)) {
    fprintf(stderr,
            "malloc: Unable to allocate %zu bytes (%s:%d)\n", 
            size, file, line);
    return NULL; 
	}
}








































//myfree
void free_error(char *file, int line){
	printf("free: Inappropriate pointer (%s:%d)", file, line);
	exit(2);
}

void myfree(void *ptr, char *file, int line){
	if((char*)ptr >= heap+MEM_SIZE) free_error(file, line);

	char* tmp = heap;
	bool found = false;
	while(tmp < heap+MEM_SIZE){
		if((char*)ptr < tmp+8) free_error(file, line);
		if(tmp+8 == ptr){
			found = true;
			break;
		}
		int jump = *(((int*)tmp)+1);
		tmp = tmp+8+jump;
	}
	if(!found) free_error(file, line);

	int prev_size = *((int*)ptr-2);
	int this_size = *((int*)ptr-1);
	if(this_size < 0) free_error(file, line);

	this_size = -this_size;
	int next_size = *((int*)(ptr + this_size) + 1);
	if(next_size < 0){
		this_size += -8 + next_size;
	}
	int real_prev_size = *(int*)(ptr-8-prev_size-4);
	if(real_prev_size < 0){
		real_prev_size += -8 + this_size;
	}
}
