PREDICTING CACHE MISS RATE

-----------------------------------------------
Observations:
> Rough sketch of the cache blocks:
  4 longs in each line since 32 bytes/8 bytes = 4.
  Line	Block1	Block2	Block3	Block4
  0	(long)	(long)	(long)	(long)	
  1	(long)	(long)	(long)	(long)
  .	.	.	.	.
  .	.	.	.	.
  .	.	.	.	.
  63	(long)	(long)	(long)	(long)
  Cache can hold 64*4*8 bytes = 2048 bytes of data
> Array is stored in row major order:
  a[0][0], a[0][1], a[0][2], ..., a[0][127],
  a[1][0], a[1][1], a[1][2], ..., a[1][127],
  .
  .
  .
  a[5][0], a[5][1], a[5][2], ..., a[5][127].
> sumA function will access array in row major order:
  a[0][0], a[0][1], a[0][2], ..., a[0][127],
  a[1][0], a[1][1], a[1][2], ..., a[1][127],
  .
  .
  .
  a[5][0], a[5][1], a[5][2], ..., a[5][127].
> sumB function will access array in column major order:
  a[0][0], a[1][0], a[2][0], a[3][0],
  a[4][0], a[5][0], a[0][1], a[1][1],
  a[2][1], a[3][1], a[4][1], a[5][1],
  .
  .
  .
  a[4][126], a[5][126], a[0][127], a[1][127],
  a[2][127], a[3][127], a[4][127], a[5][127].
> sumC function will access array in interleaving manner:
  a[0][0], a[1][0], a[0][1], a[1][1],
  a[2][0], a[3][0], a[2][1], a[3][1],
  .
  .
  .
  a[2][126], a[3][126], a[2][127], a[3][127],
  a[4][126], a[5][126], a[4][127], a[5][127].
-----------------------------------------------
Answers:
a) Miss rate = 0.25
Direct mapping means one cache line per set, so we have 64 sets. When sumA needs an element and hit a miss, it will copy a whole set of 4 longs (in row major order) from the array into cache. Since sumA need the elements in a row major order, and the elements copied from the array are also in row major order, this means the next 3 elements needed will have "cache hits" (not misses, since the elements are already copied in cache). So for every 4 access counts, 1 is miss count.

b) Miss rate = 1.00
Direct mapping means one cache line per set, so we have 64 sets. When sumB needs an element, let say a[0][0], and hit a miss, it will copy a whole set of 4 longs (in row major order) from the array into cache (line 0). When it needs the next elements in column major order, let say a[1][0], the element will not be in cache, hence a miss, so it will copy another whole set of 4 longs into cache (line 32 to be exact). When it needs the next element, let say a[2][0], the element will not be in cache, hence a miss, and it will replace the cache line which holds a[0][0] in direct mapping. 
Explanation: 
Since a[2][0], which is the 256th element in row major order array, will be at address 256*8 bytes = 2048, this means a[2][0] will replace the cache line of a[0][0], which resides on address 0 (line 0).
So when we need a[0][1], the cache block is not there anymore, hence it's another miss. So for every 4 access counts, 4 are miss counts.

c) Miss rate = 0.50
Direct mapping means one cache line per set, so we have 64 sets. When sumC needs an element, let say a[0][0], and hit a miss, it will copy a whole set of 4 longs (in row major order) from the array into cache. When it needs the next elements, let say a[1][0], the element will not be in cache, hence a miss, so it will copy another whole set of 4 longs into cache. The next two elements needed will be in the cache already (accessing array in interleaving manner in sumC), which are a[0][1] and a[1][1]. When it needs a[2][0], the cache line contains a[0][0] will be replaced, same goes to a[3][0] will replace a[1][0], and so on, with the same explanation as part (b). So for every 4 access counts, 2 are miss counts.

d) Miss rate = 1.00
Two-way set-associative means two cache lines per set, so we have 32 sets (of 2 blocks each). With similar explanation as part (b), sumB will access array in column major order, and a[0][0] will be at address 0, a[1][0] (the 128th element of the array) will be at address 1024, a[2][0] will be at address 2048. So in two-way set-associative, a[1][0] will be in the same set as a[0][0] but different lines in cache. So, a[0][0] and a[1][0] will be misses and we will copy the whole set for each of them into cache. However, when we access a[2][0], it will map to same set and same line as a[0][0] so it will replace a[0][0] with LRU policy. So when we need a[0][1], it will no longer be in cache. Same goes a[3][0] will replace a[1][0] in the set so we a[1][1] is not in cache anymore. So for every 4 access counts, 4 are miss counts.

e) Miss rate = 1.00
Four-way set-associative means four cache lines per set, so we have 16 sets (of 4 blocks each). sumB will access array in column major order, first it needs a[0][0] (a miss, copy the whole 32 bytes set), then it needs a[1][0] (a miss, copy the whole 32 bytes set), and same with a[2][0] and a[3][0]. All of them will map to same set (set 0 for exact) but different lines, because LRU policy makes sure a cache line will not be removed until all of the elements are used. However, when you access a[4][0] and a[5][0], they will replace the lines in set 0 that contain a[0][0] and a[1][0] (least recently used). This means when you need a[0][1] and a[1][1], it will be another misses. So both data blocks will be copied onto the lines that contain a[2][0] and a[3][0] (which contain data that will be accessed right after). Therefore, the lines that contain data that will be accessed next will always be replaced by the currently needed block, hence all become cache misses. So, for every 6 access counts, 6 are miss counts.

f) Miss rate = 	1.00 (worst case), 0.5 (best case)
Four-way set-associative means four cache lines per set, so we have 16 sets (of 4 blocks each). sumB will access the array in column major order. So, similar to case (e), the worst case is when each line chosen for replacement is the same as if we use LRU policy. So worst case will have 100% miss rate. 
For the best case, we use MRU (most recently used) policy, so if we ever need to replace a line, it will be the line that we just accessed. First, we copy data block of a[0][0], a[1][0], a[2][0], a[3][0] (cold misses to set 0, different lines all). Then we copied a[4][0] replacing data block of a[3][0] and a[5][0] replacing the data block of a[4][0], so the next items that we need are a[0][1], a[1][1], and a[2][1], the data will be in cache already. Then data block of a[3][1] will replace data block of a[2][0], data block of a[4][1] will replace data block of a[3][1], then data block of a[5][1] will replace data block of a[4][1]. If we continue to replace the line that we just recently accessed, let say until a[5][3] (last element we will access in set 1 for the first round), then out of 24 accesses, we will have 12 misses. Repeat for other sets.

g) Miss rate = 0.25
Direct mapping means one cache line per set, so we have 64 sets. Since we have only 120 columns, assuming a[0][0] is at address 0, then a[1][0] (the 120th element in array) will be at address 120*8 = 960, a[2][0] will be at address 240*8 = 1920, a[3][0] is at address 360*8 = 2880, and so on. So unlike the case in (b), a[2][0] will not replace the line contains a[0][0] (at line 0), but instead it will fill line 60, since 1920/32 = 60 in cache. Also, a[3][0] will fill line 26, a[4][0] will fill line 56, and a[5][0] will fill line 22. Each cache miss will copy the whole set of 4 longs that will be used for the next 3 cache reads (for the other three elements). So, for every 4 access counts, 1 is miss count.


-----------------------------------------------
IMPROVING A PROGRAM'S PERFORMANCE

Changes description:
mask1: Switched the for-loop order of i and j, and make the j loops outside of i loops. This change was made because the address was represented as [row][column], and it saves a lot of time to loop the rows outside of the columns.

mask2: Combined the ones with the same j loop.

mask3: Got rid of the variable row and col. Rearranged the content inside each j loop to make sure it only has 1 i loop inside. Moved the special cases i.e. i=0 and i=col-1 out, and then loop from 1 to cols-2. Less for loops means faster process.

mask4: First, we did same thing to j loops as what we did to i loops in mask 3: rearrange to reduce the number of loops. Then combined the lines doing computation to the same object to shorten the number of lines. After that, it's easy to see that the i loops are duplicated, so combine them together and reduce the duplications inside. Shorten the duplications inside a line.

mask5: Convert the initiation and finalizing functions the same way and combine them with existing functions. Replace the weight[j][i] in newImage[j][i] by its calculation.


Optimized results:
mask0		2801485		1.00
mask1		558627		0.19
mask2		529909		0.189
mask3		510482		0.178
mask4       	254598      	0.09
mask5       	117192      	0.041




