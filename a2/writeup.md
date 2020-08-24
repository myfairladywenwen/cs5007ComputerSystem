As to the sorting algorithm for a2, I carried out experiments below, and arrived to my conclusion.

I made a series of trials.
To get not too few results, I make 10 trials for Small, Medium and Large sizes of array.  Also, to avoid incidentally fast or slow, I randomly generated the elements of each array, value range from 0 to 1000.

1.
I first set the Small arrays to be size of 2^0, 2^1, 2^12, …till 2^9.  The output was rendered immediately, which meant that the arrays are sorted fairly quick.  And so the algorithm works well upon this level.

2.
Then I made attempted to Medium-sized arrays.  I made their sizes 2^10, 2^11, 2^12,…till 2^19. I can count seconds while the output is being printed to the screen, which meant the arrays are sorted in a longer period of time, which let me realize the slowness of the algorithm for larger arrays.

3.
Finally, I came to Large-sized arrays.  I made their sizes 2^20, 2^21, 2^22,… till 2^29, and interesting things happened.  When the array was of size 2^20, 2^21, 2^22, the output can be rendered in 10 seconds, more than 10 seconds, up to 30 seconds, and, as the array size grew, they are sorted slower and slower.  For size of 2^23, it took 45 seconds or so; for size of 2^24, it took 2 minutes or so; for size of 2^25 and 2^26, each took 3 minutes or so; for size of 2^27, it took up to 5 minutes, and it turned out to perform 2056663814 times of comparisons; for size of 2^28, it took very long time and I even lost patience to wait for the result, and 8 minutes later, it rendered output:
268435456 of elements	-175925109 times of comparisons.
This made me realize that for array of size 2^28, the number of comparisons has exceeded signed maximal integer value, which is 2,147,483,647. 

To make sure, I ran the program several times, and the “-…” times of comparison outputs were rendered at 2^29, 2^28, 2^25 sizes of arrays.  This verified my conclusion that the algorithm will not guarantee to work when array size becomes around 2^25.  But what exactly would the worst case this algorithm can handle?  My arrays are randomly generated, and so they were not guaranteed to be the worst case.  So I carried out analysis:

The run time for this algorithm is O(lgn * lgn * n), and this algorithm only works on inputs of size 2^n.  The signed maximal integer value 2^32-1.  So in order to make the algorithm work on worst case, I need to guarantee lgn * lgn * n < 2^32-1, an n is an integer of power of 2.  Do some math and we will arrive at the conclusion that max of n is 2^22. 

Based upon these,  I would have several conclusions listed below:

1.
The smallest size for this sorting algorithm to work is 2^0, that is, array of size 1;
The largest size for this sorting algorithm to work is 2^22, that is, array of size 2^22;

2.
The run time for this algorithm is O(lgn * lgn * n), and this algorithm only works on inputs of size 2^n.

3.
The run time for Bubble is O(n^2), with number of comparisons being n^2.

To gain  the bound on the number of comparisons Bubblesort will do on a list, we can do similar math:
	n^2 < 2^31 -1, n is an integer.  And so max of n is 2^15. 

4.
Compared to Bubblesort, this algorithm works faster, and in general (worst case) it can guarantee working on bigger input size (2^22 VS 2^15), but it has the requirement of input size being 2^n.

5.
As to the hardest part of this assignment, I would say is the realization of making “array things” works: divide experiment into different sizes of arrays and generate random numbers. 


Further more, my recommendation would be:

1.
If the array size is not of 2^n, don’t use this algorithm;

2.
If the array happens to be size of 2^n, and is smaller than 2^22, we can use this algorithm instead of bubblesort.

3.
Since this algorithm grows slower than bubblesort, then if we have an array of huge size, which has exceeded the bounds bubblesort can deal with(2^15), and the array size happened to be 2^n, we can use this algorithm to get the array sorted, even though it would took a bit of time.  

4.
There are many sorting algorithms which are of O(lgn * n), don’t linger on this algorithm too much and forget those faster algorithms.=)

Below is the records of two trials, just FYI.
----------
SORTING:
----------
Small:	1 of elements		        0 times of comparisons.
Small:	2 of elements		        0 times of comparisons.
Small:	4 of elements		        2 times of comparisons.
Small:	8 of elements		        10 times of comparisons.
Small:	16 of elements	        	31 times of comparisons.
Small:	32 of elements	        	87 times of comparisons.
Small:	64 of elements	        	181 times of comparisons.
Small:	128 of elements	        474 times of comparisons.
Small:	256 of elements	        1275 times of comparisons.
Small:	512 of elements	        3194 times of comparisons.
Med:	1024 of elements	        7492 times of comparisons.
Med:	2048 of elements	        17309 times of comparisons.
Med:	4096 of elements	        39117 times of comparisons.
Med:	8192 of elements	        86719 times of comparisons.
Med:	16384 of elements	        190629 times of comparisons.
Med:	32768 of elements	        394177 times of comparisons.
Med:	65536 of elements	        887986 times of comparisons.
Med:	131072 of elements       	1776227 times of comparisons.
Med:	262144 of elements       	3691995 times of comparisons.
Med:	524288 of elements       	7522551 times of comparisons.
Large:	1048576 of elements    	15496549 times of comparisons.
Large:	2097152 of elements    	31382219 times of comparisons.
Large:	4194304 of elements    	63935678 times of comparisons.
Large:	8388608 of elements    	126766764 times of comparisons.
Large:	16777216 of elements   	256566659 times of comparisons.
Large:	33554432 of elements   	512011036 times of comparisons.
Large:	67108864 of elements   	1029988041 times of comparisons.
Large:	134217728 of elements  	2056663814 times of comparisons.
Large:	268435456 of elements  	-175925109 times of comparisons.

----------
SORTING:
----------
Small:	1 of elements		0 times of comparisons.
Small:	2 of elements		1 times of comparisons.
Small:	4 of elements		5 times of comparisons.
Small:	8 of elements		19 times of comparisons.
Small:	16 of elements	        63 times of comparisons.
Small:	32 of elements	        191 times of comparisons.
Small:	64 of elements	        543 times of comparisons.
Small:	128 of elements	        1471 times of comparisons.
Small:	256 of elements	        3839 times of comparisons.
Small:	512 of elements	        9727 times of comparisons.
Med:	1024 of elements	        24063 times of comparisons.
Med:	2048 of elements	        58367 times of comparisons.
Med:	4096 of elements	        139263 times of comparisons.
Med:	8192 of elements	        327679 times of comparisons.
Med:	16384 of elements	        761855 times of comparisons.
Med:	32768 of elements	        1753087 times of comparisons.
Med:	65536 of elements	        3997695 times of comparisons.
Med:	131072 of elements       9043967 times of comparisons.
Med:	262144 of elements       20316159 times of comparisons.
Med:	524288 of elements       45350911 times of comparisons.
Large:	1048576 of elements    100663295 times of comparisons.
Large:	2097152 of elements    222298111 times of comparisons.
Large:	4194304 of elements    488636415 times of comparisons.
Large:	8388608 of elements    1069547519 times of comparisons.
Large:	16777216 of elements   -1962934273 times of comparisons.
Large:	33554432 of elements   771751935 times of comparisons.
Large:	67108864 of elements  -1912602625 times of comparisons.
