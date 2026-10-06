example: mymalloc.c memtest.c
	gcc -Wall mymalloc.c memtest.c -o example

debug: mymalloc.c memtest.c
	gcc -Wall -g mymalloc.c memtest.c -o example
