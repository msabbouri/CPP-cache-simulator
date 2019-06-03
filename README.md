# CPP-cache-simulator
In this project I built a simple simulation of a multi-level memory: a CPU with one register, three levels of cache, and a main memory. I ran the simulation on a small program of load instructions, moving values from main memory into the register, and determine the total number of cycles needed to execute the program.

The system you will be simulating is intentionally simplified. It offers

A single CPU register

A 1KB level-1 cache fully associative cache, consisting of 1 set, 4 lines, of 256 bytes per line. Accessing the L1 cache (i.e., moving data from L1 into the CPU) takes 1 cycle.

An 64KB level-2 cache, consisting of 1 set containing 64 lines of 1k bytes. Accessing the L2 cache (moving data from L2 into the CPU and L1) takes 10 cycles. Note that this can be done in parallel with loading the data into the L1 cache, so there isn’t a separate cycle cost for that.

A 1MB level-3 cache, consisting of 1 set containing 256 lines of 4k bytes each. Accessing the L3 cache takes 100 cycles. This can be done in parallel with loading the data into L2 and L1.

All caches use LRU as the cache replacement policy, and all are fully associative (1 set).

A 1GB main memory. Accessing main memory takes 1000 cycles.
