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
#define HEADERSIZE 8

int main (int argc, char **argv)
{
	void *p1 = malloc(MEMSIZE/2 - HEADERSIZE);
	void *p2 = malloc(MEMSIZE/2 - HEADERSIZE);
	free(p1);
	void *p3 = malloc(MEMSIZE/2 - HEADERSIZE*2);
	free(p2);
	void *p4 = malloc(MEMSIZE/2);
	if(p4 != NULL){
		printf("sucessful\n");
	}
	free(p4);
	free(p3);
	return EXIT_SUCCESS;
}


