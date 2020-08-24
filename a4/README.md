hw 4 is coding for a card game. deck.c has code for deck, and all other related functions\
are in a4.c.  a4_helper.c has some helper functions such as print.  a4_test.c is the test\
for the deck.c and a4.c.

Difference between stack memeory and heap memory:
Stack:
1. A temporary storage memory. It is a special area of computer's memory which stores temporary variables created by a function. In stack, variables are declared, stored and initialized during runtime.  When the computing task is complete, the memory of the variable will be automatically erased. The stack section mostly contains methods, local variable, and reference variables.
2. A stack is a linear data structure.
3. Stack memory is allocated in a contiguous block.
4. Stack memory is very limited.

Heap:
1. A memory supporting dynamic memory allocation.  Allocation and deallocation are manually done by the programmer.
2. Heap is a hierarchical data structure.
3. Heap memory is allocated in random order.
4. Heap doesn't have any limit on memory size.