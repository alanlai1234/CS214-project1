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
	void *p1 = malloc(MEMSIZE/4-HEADERSIZE);
	void *p2 = malloc(MEMSIZE/4-HEADERSIZE);
	void *p3 = malloc(MEMSIZE/4-HEADERSIZE);
	void *p4 = malloc(MEMSIZE/4-HEADERSIZE);
	free(p2);
	free(p3);
	void *p5 = malloc(MEMSIZE/2-HEADERSIZE);
	if(p5 != NULL){
		printf("successful\n");
	}

	free(p1);
	free(p4);
	free(p5);
	return EXIT_SUCCESS;
}

