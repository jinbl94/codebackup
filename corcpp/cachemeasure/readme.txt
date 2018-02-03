cachemeasure.c:
	used to measure the size of caches, including L1, L2, and L3 cache.
cacheblock.c:
	measure the size of cache block of L1 cache.
speedcompare.c:
	test memory access time and cache access time.


WARNNING:
	all the codes was designed for linux. when portting to Windows, some system calls must be replaced ( especially the time functions ). "run" is a linux shell script which can only run in Unix-like enviorment.
