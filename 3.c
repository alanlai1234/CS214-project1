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
	void *p1 = malloc(MEMSIZE-HEADERSIZE-4);
	int *p2 = malloc(sizeof(int));
	if(p2 == NULL){
		printf("successful\n");
	}

	free(p1);
	return EXIT_SUCCESS;
}

