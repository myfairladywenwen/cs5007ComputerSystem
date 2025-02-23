Wen Xie, Mar 2, 2020

# Assignment 7: Linked List with Iterator, Google Testing

## Your Info

When you are done, update this file with the following info:

* Name: Wen Xie
* How many hours did it take you to complete the assignment? 16 hours
* Did you collaborate with any other students/TAs/Professors?
  Overall I did this assignment on my own.  In the final stage when debugging, I turned to
  TA for help once.
  
* Did you use any external resources? (note them below)  No
    - tbd
    - tbd
* What was your favorite part of this assignment?
  Read through the long instruction and figure out the core is the manipulation upon linkedlist.
* What was challenging about this assignment?
  It looks really HUGE at the very beginning, but when carrying out step by step, it became
  not that mission-impossible.
* How would you improve the assignment?
  Do the iterator part more on our own instead of those already done codes provided by instructor.

## Files

* ```Makefile```: a makefile you can use to compile the assignment using the Linux command make all.
* ```LinkedList.h```: a header file that defines and documents the API to the linked list. A customer of the linked list includes this header file and uses the functions defined within in. Read through this header file very carefully to understand how the linked list is expected to behave.
* ```LinkedList_priv.h, LinkedList.c```: ```LinkedList_priv.h``` is a **private** header file included by ```LinkedList.c```; it defines the structures we diagrammed above. ```LinkedList.c``` contains the partially completed implementation of our doubly-linked list. Your task will be to finish the implementation. Take a minute and read through both files; note that there are a bunch of places in ```LinkedList.c``` that say "STEP X:" these labels identify the missing pieces of the implementation that you will finish.
* ```example_program_ll.c```: this is a simple example of how a customer might use the linked list; in it, you can see the customer allocating a linked list, adding elements to it, creating an iterator, using the iterator to navigate a bit, and then cleaning up.
* ```test_linkedlist.cc```: this file contains unit tests that we wrote to verify that the linked list implementation works correctly. The unit tests are written to use the Google Test (Links to an external site.) unit testing framework, which has similarities to Java's JUnit testing framework. Further, this test harness will assist TAs in grading your assignment: as you add more pieces to the implementation, the test harness will make it further through the unit tests, and it will print out a cumulative score along the way. You don't need to understand what's in the test driver for this assignment, though if you peek inside it, you might get hints for what kinds of things you should be doing in your implementation!
* ```solution_binaries```: in this directory, you'll find some Linux executables, including ```example_program_ll``` and ```test_suite```. These binaries were compiled with a complete, working version of ```LinkedList.c```; you can run them to explore what should be displayed when your assignment is working!