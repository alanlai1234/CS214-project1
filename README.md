set a global init variable, true means initialized, false means not
set a global char pointer, null when not initialized

header:

    * 8 byte
    * a pointer pointing to the ending of this chunk, is null means not allocated

malloc:

if not init, call malloc to create memory to the global char pointer
allocate_size = header size + smallest multiple greater equal then requested amount
find chunk:
    * set a integer prev = 0 indicating the last unallocated position
    * loop, increment every 8 bytes:
        * if current chunk is allocated:
            * if from prev to current chunk has size >= allocate_size, then allocate from prev to current chunk to the client, return
            * otherwise jump to the end via the header pointer, and set prev as the next chunk of the end
        * if current chunk is not allocated, and if from prev to current chunk has size >= allocate_size, then allocate from prev to current chunk to the client, then return
    * return NULL, print error
