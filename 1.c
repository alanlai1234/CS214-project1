#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// Compile with -DREALMALLOC to use the real malloc() instead of mymalloc()
#ifndef REALMALLOC
#include "mymalloc.h"
#endif

// Compile with -DLEAK to leak memory
#ifndef LEAK
#define LEAK 0
#endif

#define MEMSIZE 4096

struct large{
	int arr[200];
};

int main (int argc, char **argv)
{
	struct large *l1, *l2;
	l1 = malloc(sizeof(struct large));
	l2 = malloc(sizeof(struct large));
	for(int i=0;i<200;++i) l2->arr[i] = i;
	for(int i=200;i<400;++i) l1->arr[i-200] = i;
	for(int i=0;i<200;++i){
		if(l2->arr[i] != i){
			printf("allocation overridden\n");
		}
	}
	for(int i=200;i<400;++i){
		if(l1->arr[i-200] != i){
			printf("allocation overridden\n");
		}
	}
	
	return EXIT_SUCCESS;
}

