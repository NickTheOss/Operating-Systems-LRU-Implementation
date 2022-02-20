The project consists of a total of 4 files, 2 sources (lru.cpp, os2.cpp) and 2 header files (lru.h, os2.h).
In total, the Lru (Last Recent Used) algorithm was implemented using a duplicate linked list and other structures. We have 2 'bzip.trace' and 'gcc.trace' input files along with a makefile compilation file.
The following is a brief description of the program:

os2.cpp: This contains the main() function which takes as input the page size and the number q, the maximum number of lines that will be read by the input files.
The lru function returns the 2 input files to be processed by the 2 processes respectively and to produce the statistical output results.For the name of the page we keep the first 5 digits out of 8 because the last 3 are the offset. Each process after passing the file calls the add_page_to_memory() function.In addition, the is_full() function (which checks whether a table cell is empty or full) and insert_page() function(which searches the table for the full size to insert the page) are also implemented here. Finally, the program terminates by displaying a relevant message.

os2.h: This includes the function statements implemented in the os2.cpp file as well as the basic structures. The Cell class is the page table cell and consists of the id, the page name and a boolean variable to determine if the cell is empty or saturated. The PageTable class is the table of pages and consists of the page size and a pointer to each Cell (Also containing the necessary constructors, destructors).

lru.cpp: Here is the basic implementation of the lru algorithm. In the beginning, the constructor functions that initialize the required values ​​(such as the statistics we need and the indexes of the double-linked list) and the destructor of the list that frees up memory are implemented.First, the add_page_to_memory function() is called which takes as reference the character ('R' or 'W') and the page name (the first 5 digits of an address) and calls the is_exist_page() function which in turn traverses the entire list in order to find out if the page exists. If it is found and has reference = 'W', then we change the reference of the node to 'W' and then we move the node in which we found the page to the beginning of the list according to the algorithm. If the page is not found we return false. So if the page is not in the list then we call the is_full() function to see if the cell is empty. If the table is full we call the remove_page() function which removes a page by crossing the list and at the end we add the requested page to the list via the insert_page_to_node() function which takes as it's argument the address of the cell returned by the insert_page() function and the reference.


lru.h: This module contains the corresponding statements of the functions implemented in lru.cpp as well as the 2 basic classes a) Node_lru which is the list node and contains a pointer to the page table cell, the 'R' attribute or 'W', and 2 pointers for the next and previous list item b) List_lru which is the list of nodes and contains the statistics that we will display at the end, a pointer to the PageTable and the header queue. Is_empty returns true if counter = 0 (ie no page)

Implementation Language: C++

Compile command: 'make' and 'make clean' for cleaning object files.

Execution command: './os2 <page_size> <q>' ..page_size must be greater than 3 and both page_size and q must be given as arguments, otherwise a message is returned and the program terminates.
Example: './os2 100 40000'

We notice that as the page size decreases, the number of registrations increases.
Process 2 with gcc.trace has a higher number of reads and a smaller number of existing pages.

Tested in a Linux environment.