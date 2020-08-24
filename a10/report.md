// Wen Xie, cs5007 Assignment10, Apr 4
//report


I ran benchmarker with different number of threads, with one core and four cores, dealing data directory, which has more than 600000 files.
1. It turns out that using 4 cores is faster than using one core.
2. However, using multiple threads did not contribute to any improvement.  Using one thread is always the fastest way.
3. On the other side, when dealing with small size of data, e.g., running with data_tiny and data_small, it is true that using multi-thread is better.
4. But single-thread always has the best performance.


Reason for this might be:

1. create and join the threads is pretty expensive;

2. this is not "real" multi-thread because each thread has to wait the previous thread with the iterator issues, and
only when the previous thread has done with the iterator and increment it, it can get access to the iterator;
Similar situation is with the MovieIndex.  Each thread has to wait the previous thread with the AddMovieToIndex issus, and
only when the previous thread has done, other thread can get access to the index, but only one thread can.  MovieIndex and iterator are both global and this kind of issue can not be avoided.

3. Different threads must carry out context swith, which also takes up a lot of time.  That is why 4-core is better than 1-core, since it saves context switch expense.

4. The threads are dealing wiht I/O, which itself is quite expensive.

Below is the running report.
========one core, using different amounts of threads:
Took 571.514077 seconds to execute.
639209 entries in the index.
Parsing and indexing files...
file count =  52
use 27 threads.
Took 1204.548341 seconds to execute.
639209 entries in the index.
Parsing and indexing files...
file count =  52
use 10 threads.
Took 780.568489 seconds to execute.
639209 entries in the index.
Parsing and indexing files...
file count =  52
use 5 threads.
Took 696.547834 seconds to execute.
639209 entries in the index.
Parsing and indexing files...
file count =  52
use 1 threads.
Took 574.369657 seconds to execute.
639209 entries in the index.



========four cores, using different amounts of threads:
Took 548.077648 seconds to execute.
639209 entries in the index.

Parsing and indexing files...
file count =  52
use 27 threads.
Took 654.535570 seconds to execute. 
639209 entries in the index.

Parsing and indexing files...
file count =  52
use 10 threads.
Took 649.121386 seconds to execute. 
639209 entries in the index.

Parsing and indexing files...
file count =  52
use 5 threads.
Took 625.722839 seconds to execute. 
639209 entries in the index.

Parsing and indexing files...
file count =  52
use 1 threads.
Took 555.750771 seconds to execute. 
639209 entries in the index.

============deal with small data============
Took 0.146305 seconds to execute. 
20062 entries in the index.
Parsing and indexing files...
file count =  24
use 27 threads.
Took 0.154716 seconds to execute. 
20062 entries in the index.
Parsing and indexing files...
file count =  24
use 10 threads.
Took 0.172851 seconds to execute. 
20062 entries in the index.
Parsing and indexing files...
file count =  24
use 5 threads.
Took 0.148384 seconds to execute. 
20062 entries in the index.
Parsing and indexing files...
file count =  24
use 1 threads.
Took 0.142910 seconds to execute. 
20062 entries in the index.

=============deal with tiny data============
Took 0.002521 seconds to execute. 
204 entries in the index.
Parsing and indexing files...
file count =  10
use 27 threads.
Took 0.002086 seconds to execute. 
204 entries in the index.
Parsing and indexing files...
file count =  10
use 10 threads.
Took 0.001084 seconds to execute. 
204 entries in the index.
Parsing and indexing files...
file count =  10
use 5 threads.
Took 0.000950 seconds to execute. 
204 entries in the index.
Parsing and indexing files...
file count =  10
use 1 threads.
Took 0.001074 seconds to execute. 
204 entries in the index.
