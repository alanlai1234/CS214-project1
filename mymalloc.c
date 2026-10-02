#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <stdbool.h>

#define MEM_SIZE 4096

char heap[MEM_SIZE];

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
