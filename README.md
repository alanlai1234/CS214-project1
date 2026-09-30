set a global init variable, true means initialized, false means not
set a global char pointer, null when not initialized

header:
    * 8 byte
    * a pointer pointing to the ending of this chunk, is null means not allocated

metadata:
	 * status
	 * length(only payload)
	 * next
	 * previous

malloc:
   * if not init, call malloc to create memory to the global char pointer
   * allocate_size = header size + smallest multiple greater equal then requested amount
   * find chunk: //這個部分有空聊聊
       * set a integer prev = 0 indicating the last unallocated position
       * loop, increment every 8 bytes 
           * if current chunk is allocated:
               * if from prev to current chunk has size >= allocate_size, then allocate from prev to current chunk to the client, return
               * otherwise jump to the end via the header pointer, and set prev as the next chunk of the end
           * if current chunk is not allocated, and if from prev to current chunk has size >= allocate_size, then allocate from prev to current chunk to the client, then return

    * return NULL, print error

	          
Free:
    *change status to unused
	 *if .next is unused as well then 
	 		* change length equal (the original length + the next metadata + the next payload)
	 		* change .next to .next.next
	 *if .prev is unused then 
	 		* change .prev.length
			* change .prev.next
check:
	 *no chunk overlaps
	 *no continuous empty trunk
	 *no chunk go over the limits


目前寫的內容需要調整的地方 by.gpt **我們有空討論一下喔

8-byte header，只存結尾指標，NULL 表示未配置              	跟下面四欄位 metadata 是不同方案，不能直接混著使用
status / length / next / previous	                  如果選這個方案，就用這份 metadata 的實際大小規劃 header
初始化時呼叫 malloc() 建立 heap	                        這份作業要求使用老師提供的固定 union 陣列
額外的 global char pointer	                           老師只特別允許額外的 static int 初始化旗標；走訪用的指標可以放在函式內作為區域變數
