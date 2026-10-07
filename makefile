memtest: mymalloc.c memtest.c
	gcc -Wall mymalloc.c memtest.c -o example

gdb: mymalloc.c memtest.c
	gcc -Wall -g mymalloc.c memtest.c -o example

1: mymalloc.c 1.c
	gcc -Wall mymalloc.c 1.c -o test

2: mymalloc.c 2.c
	gcc -Wall mymalloc.c 2.c -o test

3: mymalloc.c 3.c
	gcc -Wall mymalloc.c 3.c -o test

4: mymalloc.c 4.c
	gcc -Wall mymalloc.c 4.c -o test

5: mymalloc.c 5.c
	gcc -Wall mymalloc.c 5.c -o test

6: mymalloc.c 6.c
	gcc -Wall mymalloc.c 6.c -o test

7: mymalloc.c 7.c
	gcc -Wall mymalloc.c 7.c -o test
