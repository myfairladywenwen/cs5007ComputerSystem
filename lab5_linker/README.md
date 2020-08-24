// Wen Xie  Apr 16
# Linker Lab

See Canvas for details.

# Submission

Modify this readme with the following information. Copy this info to the Canvas submission. Commit and push to Github.

* Commit your hack.c file.
* Put the following in your README.md file: 
   * Name(s): Wen Xie
   * How many hours did it take you to complete this lab? 1hour
   * Did you collaborate with any other students/TAs/Professors? Linni Cai
   * Did you use any external resources? (Cite them below)
      * google a lot
      https://softwareengineering.stackexchange.com/questions/360452/splitting-large-c-project
      
      https://medium.com/@meghamohan/everything-you-need-to-know-about-libraries-in-c-e8ad6138cbb4


   * How does breaking code into libraries like this save compile time?
     Libraries help to make the program as separate smaller files, and separate compilation saves time. If we change one file, we just need to compile that file only, and relink.

   * How does the linker find the code needed for our executable? Does all of the code live together in one executable?
   Using environment variable;
   LD_LIBRARY_PATH environment variable
   If we use static libraries, the codes will be locked into the program, whereas, if we use dynamic libraries, they will exist as separate files out side the executable file.
   
   * (Optional) What was your favorite part of the assignment?
   * (Optional) How would you improve the assignment?
