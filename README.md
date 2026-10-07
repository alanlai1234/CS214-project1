Alan Lai, kl1210,Cheng Chan Lee, cl1814

Design Notes
---
We set the header as 8 byte with two int variables prev_size and size. Prev_size is the size of the chunk before it, so that its easy to check free coalescing. Size can be negative and positive, where <=0 means that this block is unused, >0 means this block is used, and abs(size) is the actual size of the chunk. We specifically made 0 as unused because then if the chunk after it is freed it can coalesce with it and gain 8 more bytes(the header). 

Requirements
---
1.  Requirements: malloc reserve free chunks, leak detection
    Method: When successful, malloc() returns a pointer to an object that does not overlap with any other allocated object. Then when program finishes should report memory leak because we intentionally not free it.
    Test: Allocate two large arrays, say both with 200 elements. Then fill the first one with 200-399, the second one with 0-199. Then check if the numbers are still intact. Don't free the two chunks.
2.  Requirements: Coalesce free chunks, free dallocates
    Method: All the allocation should be successful, where the middle two chunks are freed, and are merged so that a chunk can fill the gap.
    Test: Allocate four chunks that equally fills the heap, free the middle two, then allocate one that is the size of the two chunks freed.
3.  Requirements: Align by 8 bytes, malloc detect requests that exceeds max heap size
    Method: First allocation should fill the heap. Then the int allocated at the end should return null since there's no space left.
    Test: Allocate a chunk that is 4 bytes smaller then the max heap size, then allocate an int, should return null.
4.  Requirements: must not free addresses not from malloc
    Method: Should report error and exit.
    Test: Declare a int variable and call free on it.
5.  Requirements: must not free addresses not at the start of a chunk
    Method: Should report error and exit.
    Test: Allocate a chunk, minus 8 to the pointer and call free on it.
6.  Requirements: calling free a second time on the same address
    Method: Should report error and exit.
    Test: Allocate a chunk, free it two consecutive times.
7.  Requirements: a space of 8 byte is a chunk of size 0, unused, where it can be coalesced later.
    Method: Everything should allocate succesfully and fill the heap.
    Test: Allocate two chunks of the size of half the max size, then free the first one. Then allocate a chunk of size of half the max size minus one header size, now free the second chunk allocated originally, then you should be able to allocate a chunk of size of half the max size plus a header size.
